#include <stdint.h>

#include "debug.h"
#include "strutils.h"
#include "pins.h"
#include "avr_spi.h"
#include "enc28j60_defs.h"

#define ENC28J60_CS_AS_OUTPUT	(ENC28J60_CS_DDR	|= (1 << ENC28J60_CS_OFFSET))
#define ENC28J60_CS_SET_HIGH	(ENC28J60_CS_PORT	|= (1 << ENC28J60_CS_OFFSET))
#define ENC28J60_CS_SET_LOW	(ENC28J60_CS_PORT	&= ~(1 << ENC28J60_CS_OFFSET))
#define ENC28J60_INT_AS_INPUT	(ENC28J60_INT_DDR	&= ~(1 << ENC28J60_INT_OFFSET))

#define ENC_SELECT	ENC28J60_CS_SET_LOW
#define ENC_DESELECT	ENC28J60_CS_SET_HIGH

#if 0
static void enc_spi_write(const uint8_t op, const uint8_t addr, const uint8_t data)
{
	uint8_t header;
	uint8_t payload;

	dbg("enc28j60: spi write\r\n");

	ENC28J60_SPI_CS_LOW;

	header = op << 5;
	header |= addr & 0x1f;
	payload = data;

	avr_spi_send(header);
	avr_spi_send(payload);

	ENC28J60_SPI_CS_HIGH;
}
#endif

static char enc_rcr(const char in)
{
	char out;
	ENC_SELECT;
	avr_spi_trx(in);
	out = avr_spi_trx(0xff);
	ENC_DESELECT;
	return out;
}

static void enc_wcr(const char addr, const char data)
{
	char op;
	op = addr;
	op |= WCR;
	ENC_SELECT;
	avr_spi_trx(op);
	avr_spi_trx(data);
	ENC_DESELECT;
}

static void enc_bfs(const char addr, const char mask)
{
	char op;
	op = addr;
	op |= BFS; /* set Bit Field Set operation */
	ENC_SELECT;
	avr_spi_trx(op);
	avr_spi_trx(mask);
	ENC_DESELECT;
}

static void enc_bfc(const char addr, const char mask)
{
	char op;
	op = addr;
	op |= BFC; /* set Bit Field Clear operation */
	ENC_SELECT;
	avr_spi_trx(op);
	avr_spi_trx(mask);
	ENC_DESELECT;
}

static void enc_gpioinit(void)
{
	/* make CS pin output and set output high */
	ENC28J60_CS_AS_OUTPUT;
	ENC28J60_CS_SET_HIGH;

	/* make INT pin an input */
	ENC28J60_INT_AS_INPUT;
}

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

static void enc_txbufinit(void)
{
}

static void enc_bank(const char bank)
{
	enc_wcr(ECON1, bank);
}

void enc28j60_init(void)
{
	int i;
	char c;
	char str[3+1];
	char reg;

	/* GPIO configuration */
	enc_gpioinit();

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
