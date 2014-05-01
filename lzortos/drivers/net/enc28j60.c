/******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdint.h>

#include "config.h"
#include "debug.h"
#include "strutils.h"
#include "pins.h"
#include "avr_spi.h"
#include "enc28j60_defs.h"

/******************************************************************************
 * Macro symbols
 ******************************************************************************/

#define ENC28J60_CS_AS_OUTPUT	(GPIO_ENC28J60_CS_DDR	|= (1 << GPIO_ENC28J60_CS_OFFSET))
#define ENC28J60_CS_SET_HIGH	(GPIO_ENC28J60_CS_PORT	|= (1 << GPIO_ENC28J60_CS_OFFSET))
#define ENC28J60_CS_SET_LOW	(GPIO_ENC28J60_CS_PORT	&= ~(1 << GPIO_ENC28J60_CS_OFFSET))
#define ENC28J60_INT_AS_INPUT	(GPIO_ENC28J60_INT_DDR	&= ~(1 << GPIO_ENC28J60_INT_OFFSET))

#define ENC_SELECT	ENC28J60_CS_SET_LOW
#define ENC_DESELECT	ENC28J60_CS_SET_HIGH

/******************************************************************************
 * Private functions
 ******************************************************************************/

//#define ENC_REGIO_NEW

#ifdef ENC_REGIO_NEW
static unsigned char enc_regio(const uint8_t op, const uint8_t addr, const uint8_t data)
{
	unsigned char rv;
	uint8_t header;
	uint8_t payload;

	dbg("enc28j60: spi write\r\n");

	header = op << 5;
	header |= addr & 0x1f;
	payload = data;

	ENC_SELECT;

	avr_spi_trx(header);
	rv = avr_spi_trx(payload);

	ENC_DESELECT;

	return rv;
}
#endif

/*-----------------------------------------------------------------------------
 * SPI Command Instructions
 *----------------------------------------------------------------------------*/

/* Read Control Register instruction */
static char enc_rcr(const char in)
{
#ifndef ENC_REGIO_NEW
	char out;
	ENC_SELECT;
	avr_spi_trx(in);
	out = avr_spi_trx(0xff);
	ENC_DESELECT;
	return out;
#else
	return enc_regio(RCR, in, 0xff);
#endif
}

/* Write Control Register instruction */
static void enc_wcr(const char addr, const char data)
{
#ifndef ENC_REGIO_NEW
	char op;
	op = addr;
	op |= WCR;
	ENC_SELECT;
	avr_spi_trx(op);
	avr_spi_trx(data);
	ENC_DESELECT;
#else
	enc_regio(WCR, addr, data);
#endif
}

/* Bit Field Set instruction */
static void enc_bfs(const char addr, const char mask)
{
#ifndef ENC_REGIO_NEW
	char op;
	op = addr;
	op |= BFS; /* set Bit Field Set operation */
	ENC_SELECT;
	avr_spi_trx(op);
	avr_spi_trx(mask);
	ENC_DESELECT;
#else
	enc_regio(BFS, addr, mask);
#endif
}

/* Bit Field Clear instruction */
static void enc_bfc(const char addr, const char mask)
{
#ifndef ENC_REGIO_NEW
	char op;
	op = addr;
	op |= BFC; /* set Bit Field Clear operation */
	ENC_SELECT;
	avr_spi_trx(op);
	avr_spi_trx(mask);
	ENC_DESELECT;
#else
	enc_regio(BFC, addr, mask);
#endif
}

/*-----------------------------------------------------------------------------
 * Initialization
 *----------------------------------------------------------------------------*/

/* Initialize GPIOs */
static void enc_gpioinit(void)
{
	/* make CS pin output and set output high */
	ENC28J60_CS_AS_OUTPUT;
	ENC28J60_CS_SET_HIGH;

	/* make INT pin an input */
	ENC28J60_INT_AS_INPUT;
}

/* Register Bank Selection ***************************************************/

/* Select a memory bank */
static void enc_bank(const char bank)
{
	enc_wcr(ECON1, (bank & BSEL_MASK) << BSEL_OFFSET);
}

static void enc_bank_test(const char reg)
{
	int i;
	char c;
	char str[3+1];

	for (i = 0; i < 4; i++) {

		enc_bank(i);

		c = enc_rcr(reg);

		itoa(reg, str, 16);
		dbg("enc28J60: ");
		dbg("*(0x");
		dbg(str);
		dbg(")");

		itoa(c, str, 16);
		dbg(" = 0x");
		dbg(str);
		dbg("\r\n");
	}
}

/* Misc **********************************************************************/

static void enc_cfg_dump(const unsigned short rxbufstart,
			const unsigned short rxbufend,
			unsigned char hwaddr[6],
			unsigned short framelen,
			unsigned char fd)
{
	char str_rxbufstart[5];
	char str_rxbufend[5];
	char str_hwaddr[6][3];
	char str_framelen[5];

	itoa(rxbufstart, str_rxbufstart, 16);
	itoa(rxbufend, str_rxbufend, 16);
	itoa(framelen, str_framelen, 10);

	itoa(hwaddr[5], str_hwaddr[5], 16);
	itoa(hwaddr[4], str_hwaddr[4], 16);
	itoa(hwaddr[3], str_hwaddr[3], 16);
	itoa(hwaddr[2], str_hwaddr[2], 16);
	itoa(hwaddr[1], str_hwaddr[1], 16);
	itoa(hwaddr[0], str_hwaddr[0], 16);

	dbg("enc28j60: rxbufstart: 0x");
	dbg(str_rxbufstart);
	dbg("\r\n");

	dbg("enc28j60: rxbufend:   0x");
	dbg(str_rxbufend);
	dbg("\r\n");

	dbg("enc28j60: hwaddr: ");
	dbg(str_hwaddr[5]);
	dbg(":");
	dbg(str_hwaddr[4]);
	dbg(":");
	dbg(str_hwaddr[3]);
	dbg(":");
	dbg(str_hwaddr[2]);
	dbg(":");
	dbg(str_hwaddr[1]);
	dbg(":");
	dbg(str_hwaddr[0]);
	dbg("\r\n");

	dbg("enc28j60: framelen:   ");
	dbg(str_framelen);
	dbg("\r\n");

	dbg("enc28j60: duplex:     ");
	if (fd)
		dbg("full");
	else
		dbg("half");
	dbg("\r\n");
}

/* Clock *********************************************************************/

/* Check if the oscillator start-up timer has expired and
 * the device is ready to perform regular operation */
static int enc_clkready(void)
{
	char s;
	s = enc_rcr(ESTAT);
	/* poll ESTAT.CLKRDY bit */
	if (s & (1 << CLKRDY))
		return 1;
	return 0;
}

/* Optional ******************************************************************/

/* Configure the optional clock output pin (CLKOUT).
 *
 * Paramters
 *   ps		See enc28j60_clkout_ps for values
 */
static void enc_clkout(const unsigned char ps)
{
	unsigned char regv = (ps << COCON_OFFSET) & COCON_MASK;
	enc_bank(BANK3);
	enc_wcr(ECOCON, regv);
}

/* Ethernet Buffer ***********************************************************/

/* Initialize the ethernet buffer.
 *
 * Will configure the size of the receive buffer. The remaining space will be
 * used as the transmission buffer.
 */
static void enc_bufinit(const unsigned short rxbufstart,
			const unsigned short rxbufend)
{
	unsigned short rxbufread = rxbufstart;

	/* Select bank 0 for access to EXRSTL, ERXSTH, ERXNDL, ERXNDH,
	 * RXRDPTL and RXRDPTH */

	enc_bank(BANK0);

	/* set receive buffer start poitner (ERXST) */
	enc_wcr(ERXSTL, rxbufstart);
	enc_wcr(ERXSTH, rxbufstart >> 8);

	/* set receive buffer end pointer (ERXND) */
	enc_wcr(ERXNDL, rxbufend);
	enc_wcr(ERXNDH, rxbufend >> 8);

	/* set receive buffer read pointer (ERXRDPT) */
	enc_wcr(ERXRDPTL, rxbufread);
	enc_wcr(ERXRDPTH, rxbufread >> 8);
}

/* MAC ***********************************************************************/

static void enc_mac_setframelen(const unsigned short framelen)
{
	/* Select bank 2 for access to MAMXFLL and MAMXFLH */
	enc_bank(BANK2);

	/* Set Maximum Frame Lenght */
	enc_wcr(MAMXFLL, framelen);
	enc_wcr(MAMXFLH, framelen >> 8);
}

static void enc_mac_sethwaddr(unsigned char hwaddr[6])
{
	/* Select bank 3 for access to MAADR registers */
	enc_bank(BANK3);

	/* Write MAC address */
	enc_wcr(MAADR1, hwaddr[0]);
	enc_wcr(MAADR2, hwaddr[1]);
	enc_wcr(MAADR3, hwaddr[2]);
	enc_wcr(MAADR4, hwaddr[3]);
	enc_wcr(MAADR5, hwaddr[4]);
	enc_wcr(MAADR6, hwaddr[5]);
}

/* Send MAC Initialization Settings */

static void enc_macinit(unsigned char hwaddr[6],
			const unsigned short framelen,
			const unsigned char fd)
{
	unsigned char v;

	/* Select bank 2 for access to MACON1, MACON3, MACON4, MABBIPG,
	 * MAIPGL, MAIPGH, MAMXFLL, MAMXFLH */

	enc_bank(BANK2);

	/*--- Configure MACON1 ----------------------------------------------*/

	v = 0;

	if (fd) {
		/* Allow the MAC to transmit pause control frames (needed for
		 * flow control in full duplex) */

		v |= (1 << TXPAUS);

		/* Inhibit transmissions when pause control frames are received
		 * (normal operation) */

		v |= (1 << RXPAUS);
	}

	/* Enable packets to be received by the MAC */

	v |= (1 << MARXEN);

	enc_wcr(MACON1, v);

	/*--- Configure MACON3 ----------------------------------------------*/

	/* TODO use func arg */
	enum enc28j60_padcfg padcfg = PADCFG_PAD60CRC;

	v = 0;

	/* Setup Automatic Pad and CRC Configuration bits */

	v |= (padcfg << PADCFG_OFFSET) & PADCFG_MASK;

	/* Make MAC append valid CRC to all frames transmitted */

	/* TODO use func arg */
	v |= (1 << TXCRCEN);

	/* Set duplex mode */

	if (fd)
		v |= (1 << FULDPX);

	enc_wcr(MACON3, v);

	/*--- Configure MACON4 ----------------------------------------------*/

	v = 0;

	/* Adjust transmission behavior when half-duplex is used */

	if (!fd) {
		/* When the medium is occupied, the MAC will wait indefinitley
		 * for it to become free when attempting to transmit. */
		v |= (1 << DEFER);

		enc_wcr(MACON4, v);
	}

	/*--- Frame Lenght --------------------------------------------------*/

	enc_mac_setframelen(framelen);

	/*--- Inter-Packet Gap ----------------------------------------------*/

	/* Configure Back-to-Back Inter-Packet gap */

	enc_wcr(MABBIPG, (fd ? 0x15 : 0x12));

	/* Configure non-Back-to-Back Inter-Packet gap */

	enc_wcr(MAIPGL, 0x12);

	if (!fd)
		enc_wcr(MAIPGH, 0x0c);

	/*--- Collision -----------------------------------------------------*/

	if (!fd) {
		/* Set Retransmission and Collision window */
		/* TODO use func arg */
		enc_wcr(MACLCON1, 0);
		enc_wcr(MACLCON2, 0);
	}

	/*--- MAC Address ---------------------------------------------------*/

	enc_mac_sethwaddr(hwaddr);
}

/* PHY ***********************************************************************/

static unsigned short enc_phy_regread(const unsigned char reg)
{
	unsigned short rv;

	/* Select bank 2 for access to MIREGADR and MICMD */

	enc_bank(BANK2);

	/* Write PHY register address */

	enc_wcr(MIREGADR, reg);

	/* Start the read operation */

	enc_bfs(MICMD, (1 << MIIRD));

	/* Select bank 3 for access to MISTAT */

	enc_bank(BANK3);

	/* Wait until ready */

	while (enc_rcr(MISTAT) & (1 << BUSY))
		;

	/* Switch back to bank 2 */

	enc_bank(BANK2);

	/* Clear the read operation bit */

	enc_bfc(MICMD, (1 << MIIRD));

	/* Read register */

	rv = enc_rcr(MIRDL);
	rv |= (enc_rcr(MIRDH) << 8);

	return rv;
}

static void enc_phy_regwrite(const unsigned char reg, const unsigned short v)
{
	/* Select bank 2 for access to MIREGADR */

	enc_bank(BANK2);

	/* Write PHY register address */

	enc_wcr(MIREGADR, reg);

	/* Write the register value */

	enc_wcr(MIWRL, v);
	enc_wcr(MIWRH, v >> 8); /* Writing this reg starts the operation */

	/* Select bank 3 for access to MISTAT */

	enc_bank(BANK3);

	/* Wait until ready */

	while (enc_rcr(MISTAT) & (1 << BUSY))
		;
}

static void enc_phyinit(const unsigned char fd)
{
	unsigned short v;

	/* Set duplex mode */

	if (fd) {
		v = 0;
		v |= (1 << PDPXMD);
		enc_phy_regwrite(PHCON1, v);
	}

	/* Disable loopback for half-duplex */

	if (!fd) {
		v = 0;
		v |= (1 << HDLDIS);
		enc_phy_regwrite(PHCON2, v);
	}

	/* Configure LEDs */

	v = enc_phy_regread(PHLCON);

	/* LED A (yellow) */
	v &= ~LACFG_MASK;
	v |= (0x8 << LACFG_OFFSET) & LACFG_MASK;
	/* LED B (green) */
	v &= ~LBCFG_MASK;
	v |= (0x8 << LBCFG_OFFSET) & LBCFG_MASK;

	enc_phy_regwrite(PHLCON, v);
}

/******************************************************************************
 * Public functions
 ******************************************************************************/

void enc28j60_init(unsigned char hwaddr[6],
		const unsigned short framelen,
		const unsigned char fd)
{
	unsigned short rxbufstart = 0x1FF;
	unsigned short rxbufend = 0x1FFF;

	enc_cfg_dump(rxbufstart, rxbufend, hwaddr, framelen, fd);

	/* GPIO configuration */
	enc_gpioinit();

	enc_bank_test(0x19);

	/* Set clock output configuration (optional) */
	enc_clkout(CLKOUT_DIV2);

	/* receive buffer */
	enc_bufinit(rxbufstart, rxbufend);

	/* receive filters (ERXFCON) */

	/* Wait for the Oscillator Start-Up timer to expire
	 * so MAC and PHY can be initialized. */
	while (!enc_clkready())
		;

	/* configure MAC registers */
	enc_macinit(hwaddr, framelen, fd);
	/* configure PHY registers */
	enc_phyinit(fd);

	dbg("enc28j60: ready!\r\n");
}
