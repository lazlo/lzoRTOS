#include <stdint.h>

#include "debug.h"
#include "pins.h"

#define ENC28J60_SPI_CS_HIGH	(ENC28J60_CS_PORT &= ~(1 << ENC28J60_CS_OFFSET))
#define ENC28J60_SPI_CS_LOW	(ENC28J60_CS_PORT |= (1 << ENC28J60_CS_OFFSET))

#include "avr_spi.h"
#include "enc28j60_defs.h"

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

static void enc_gpioinit(void)
{
	/* make CS pin output and set output high */
	ENC28J60_CS_DDR |= (1 << ENC28J60_CS_OFFSET);
	ENC28J60_CS_PORT |= (1 << ENC28J60_CS_OFFSET);

	/* make INT pin an input */
	ENC28J60_INT_DDR &= ~(1 << ENC28J60_INT_OFFSET);
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

void enc28j60_init(void)
{
	/* GPIO configuration */
	enc_gpioinit();
	/* receive buffer */
	enc_rxbufinit();
	/* transmit buffer */
	enc_txbufinit();
	/* receive filters (ERXFCON) */

	/* poll ESTAT.CLKRDY bit */

	/* configure MAC registers */
	/* configure PHY registers */
}
