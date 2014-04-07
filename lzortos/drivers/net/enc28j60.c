/******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdint.h>

#include "debug.h"
#include "strutils.h"
#include "pins.h"
#include "avr_spi.h"
#include "enc28j60_defs.h"

/******************************************************************************
 * Macro symbols
 ******************************************************************************/

#define ENC28J60_CS_AS_OUTPUT	(ENC28J60_CS_DDR	|= (1 << ENC28J60_CS_OFFSET))
#define ENC28J60_CS_SET_HIGH	(ENC28J60_CS_PORT	|= (1 << ENC28J60_CS_OFFSET))
#define ENC28J60_CS_SET_LOW	(ENC28J60_CS_PORT	&= ~(1 << ENC28J60_CS_OFFSET))
#define ENC28J60_INT_AS_INPUT	(ENC28J60_INT_DDR	&= ~(1 << ENC28J60_INT_OFFSET))

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

/* Initialize receive buffer */
static void enc_rxbufinit(void)
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

/* Initialize transmit buffer */
static void enc_txbufinit(void)
{
}

/* Select a memory bank */
static void enc_bank(const char bank)
{
	enc_wcr(ECON1, bank);
}

/* Check if the oscillator start-up timer has expired and
 * the device is ready to perform regular operation */
static int enc_clkready(void)
{
	char s;
	s = enc_rcr(ESTAT);
	if (s & (1 << CLKRDY))
		return 1;
	return 0;
}

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

/******************************************************************************
 * Public functions
 ******************************************************************************/

void enc28j60_init(void)
{
	int i;
	char c;
	char str[3+1];
	char reg;

	/* GPIO configuration */
	enc_gpioinit();

	/* Wait for the Oscillator Start-Up timer to expire */
	while (!enc_clkready())
		;

	/* Set clock output configuration (optional) */
	enc_clkout(CLKOUT_DIV2);

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

	/* receive buffer */
	enc_rxbufinit();
	/* transmit buffer */
	enc_txbufinit();
	/* receive filters (ERXFCON) */

	/* poll ESTAT.CLKRDY bit */

	/* configure MAC registers */
	/* configure PHY registers */
	dbg("enc28j60: ready!\r\n");
}
