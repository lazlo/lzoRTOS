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

static void enc_bank_test(void)
{
	int i;
	char c;
	char str[3+1];
	char reg;

	for (i = 0; i < 4; i++) {

		enc_bank(i);

		reg = ECON1;
		c = enc_rcr(reg);

		itoa(reg, str, 16);
		dbg("enc28J60: ");
		dbg("*(0x");
		dbg(str);
		dbg(")");

		itoa(c, str, 16);
		dbg(" = ");
		dbg(str);
		dbg("\r\n");
	}
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
static void enc_bufinit(void)
{
#if 0
	/* set receive buffer start poitner (ERXST) */
	enc_spi_write(WCR, ERXSTL, 0);
	enc_spi_write(WCR, ERXSTH, 0);

	/* set receive buffer end pointer (ERXND) */
	enc_spi_write(WCR, ERXNDL, 0xf);
	enc_spi_write(WCR, ERXNDH, 0xff);

	/* set receive buffer read pointer (ERXRDPT) */
	enc_spi_write(WCR, ERXRDPTL, 0);
	enc_spi_write(WCR, ERXRDPTH, 0);
#endif
}

/* MAC ***********************************************************************/

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

	/* Set Maximum Frame Lenght */
	enc_wcr(MAMXFLL, framelen);
	enc_wcr(MAMXFLH, framelen >> 8);

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

/* PHY ***********************************************************************/

static void enc_phyinit(void)
{
}

/******************************************************************************
 * Public functions
 ******************************************************************************/

void enc28j60_init(unsigned char hwaddr[6],
		const unsigned short framelen,
		const unsigned char fd)
{
	/* GPIO configuration */
	enc_gpioinit();

	/* Set clock output configuration (optional) */
	enc_clkout(CLKOUT_DIV2);

	/* receive buffer */
	enc_bufinit();

	/* receive filters (ERXFCON) */

	/* Wait for the Oscillator Start-Up timer to expire
	 * so MAC and PHY can be initialized. */
	while (!enc_clkready())
		;

	/* configure MAC registers */
	enc_macinit(hwaddr, framelen, fd);
	/* configure PHY registers */
	enc_phyinit();

	dbg("enc28j60: ready!\r\n");
}
