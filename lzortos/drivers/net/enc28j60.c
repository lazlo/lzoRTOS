#include <stdint.h>

#include "avr_spi.h"

#define spi_send	avr_spi_send

/* SPI Instruction Set for the ENC28J60 */
enum enc28j60_instr {
	RCR	= 0,	/* Read Control Register */
	RBM	= 1,	/* Read Buffer Memory */
	WCR	= 2,	/* Write Control Register */
	WBM	= 3,	/* Write Buffer Memory */
	BFS	= 4,	/* Bit Field Set */
	BFC	= 5,	/* Bit Field Clear */
	SRC	= 7	/* System Reset Command (Soft Reset) */
};

/* Memory Banks */
enum enc28j60_bank {
	BANK0,
	BANK1,
	BANK2,
	BANK3
};

/* Control Registers - Bank 0 */
enum enc28j60_bank0_reg {
	ERDPTL		= 0x00,	/* Read Pointer Low Byte */
	ERDPTH		= 0x01,	/* Read Pointer High Byte */
	EWRPTL		= 0x02,	/* Write Pointer Low Byte */
	EWRPTH		= 0x03,	/* Write Pointer High Byte */
	ETXSTL		= 0x04,	/* TX Start Low Byte */
	ETXSTH		= 0x05,	/* TX Start High Byte */
	ETXNDL		= 0x06,	/* TX End Low Byte */
	ETXNDH		= 0x07,	/* TX End High Byte */
	ERXSTL		= 0x08,	/* RX Start Low Byte */
	ERXSTH		= 0x09,	/* RX Start High Byte */
	ERXNDL		= 0x0a,	/* RX End Low Byte */
	ERXNDH		= 0x0b,	/* RX End High Byte */
	ERXRDPTL	= 0x0c,	/* RX RD Pointer Low Byte */
	ERXRDPTH	= 0x0d,	/* RX RD Pointer High Byte */
	ERXWRPTL	= 0x0e,	/* RX RW Pointer Low Byte */
	ERXWRPTH	= 0x0f,	/* RX RW Pointer High Byte */
	EDMASTL		= 0x10,	/* DMA Start Low Byte */
	EDMASTH		= 0x11,	/* DMA Start High Byte */
	EDMANDL		= 0x12,	/* DMA End Low Byte */
	EDMANDH		= 0x13,	/* DMA End High Byte */
	EDMADSTL	= 0x14,	/* DMA Destination Low Byte */
	EDMADSTH	= 0x15,	/* DMA Destination High Byte */
	EDMACSL		= 0x16,	/* DMA Checksum Low Byte */
	EDMACSH		= 0x17,	/* DMA Checksum High Byte */
	EMPTY1		= 0x18,	/* empty */
	EMPTY2		= 0x19	/* empty */
};

/* Control Registers - Bank 1 */
enum enc28j60_bank1_reg {
	EHT0		= 0x00,	/* Hash Table Byte 0 */
	EHT1		= 0x01,	/* Hash Table Byte 1 */
	EHT2		= 0x02,	/* Hash Table Byte 2 */
	EHT3		= 0x03,	/* Hash Table Byte 3 */
	EHT4		= 0x04,	/* Hash Table Byte 4 */
	EHT5		= 0x05,	/* Hash Table Byte 5 */
	EHT6		= 0x06,	/* Hash Table Byte 6 */
	EHT7		= 0x07,	/* Hash Table Byte 7 */
	EPMM0		= 0x08,	/* Pattern Match Mask Byte 0 */
	EPMM1		= 0x09,	/* Pattern Match Mask Byte 1 */
	EPMM2		= 0x0a,	/* Pattern Match Mask Byte 2 */
	EPMM3		= 0x0b,	/* Pattern Match Mask Byte 3 */
	EPMM4		= 0x0c,	/* Pattern Match Mask Byte 4 */
	EPMM5		= 0x0d,	/* Pattern Match Mask Byte 5 */
	EPMM6		= 0x0e,	/* Pattern Match Mask Byte 6 */
	EPMM7		= 0x0f,	/* Pattern Match Mask Byte 7 */
	EPMCSL		= 0x10,	/* Pattern Match Checksum Low Byte */
	EPMCSH		= 0x11,	/* Pattern Match Checksum High Byte */
	EMPTY3		= 0x12,	/* empty */
	EMPTY4		= 0x13,	/* empty */
	EPMOL		= 0x14,	/* Pattern Match Offset Low Byte */
	EPMOH		= 0x15,	/* Pattern Match Offset High Byte */
	RESERVED1	= 0x16,	/* reserved */
	RESERVED2	= 0x17,	/* reserved */
	ERXFCON		= 0x18,	/* Receive Filter Configuration */
	EPKTCNT		= 0x19	/* Ethernet Packet Count */
};

/* Control Registers - Bank 2 */
enum enc28j60_bank2_reg {
	MACON1		= 0x00,	/* MAC Control Register 1 */
	RESERVED3	= 0x01,	/* reserved */
	MACON3		= 0x02,	/* MAC Control Register 3 */
	MACON4		= 0x03,	/* MAC Control Register 4 */
	MABBIPG		= 0x04,	/* Back-to-Back Inter-Packet Gap */
	EMPTY5		= 0x05,	/* empty */
	MAIPGL		= 0x06,	/* Non-Back-to-Back Inter-Packet Gap Low Byte */
	MAIPGH		= 0x07,	/* Non-Back-to-Back Inter-Packet Gap High Byte */
	MACLCON1	= 0x08,
	MACLCON2	= 0x09,
	MAMXFLL		= 0x0a,	/* Maximum Frame Length Low Byte */
	MAMXFLH		= 0x0b,	/* Maximum Frame Length High Byte */
	RESERVED4	= 0x0c,	/* reserved */
	RESERVED5	= 0x0d,	/* reserved */
	RESERVED6	= 0x0e,	/* reserved */
	EMPTY6		= 0x0f,	/* empty */
	RESERVED7	= 0x10,	/* reserved */
	RESERVED8	= 0x11,	/* reserved */
	MICMD		= 0x12,	/* MII Command Register */
	EMPTY7		= 0x13,	/* empty */
	MIREGADR	= 0x14,	/* MII Register Address */
	RESERVED9	= 0x15,	/* reserved */
	MIWRL		= 0x16,	/* MII Write Data Low Byte */
	MIWRH		= 0x17,	/* MII Write Data High Byte */
	MIRDL		= 0x18,	/* MII Read Data Low Byte */
	MIRDH		= 0x19	/* MII Read Data High Byte */
};

/* Control Registers - Bank 3 */
enum enc28j60_bank3_reg {
	MAADR5		= 0x00,	/* MAC Address Byte 5 */
	MAADR6		= 0x01,	/* MAC Address Byte 6 */
	MAADR3		= 0x02,	/* MAC Address Byte 3 */
	MAADR4		= 0x03,	/* MAC Address Byte 4 */
	MAADR1		= 0x04,	/* MAC Address Byte 1 */
	MAADR2		= 0x05,	/* MAC Address Byte 2 */
	EBSTSD		= 0x06,	/* Built-in Self-Test Fill Speed */
	EBSTCON		= 0x07,	/* Ethernet Self-Test Control Register */
	EBSTCSL		= 0x08,	/* Built-in Self-Test Checksum Low Byte */
	EBSTCSH		= 0x09,	/* Built-in Self-Test Checksum High Byte */
	MISTAT		= 0x0a,	/* MII Status Register */
	EMPTY8		= 0x0b,	/* empty */
	EMPTY9		= 0x0c,	/* empty */
	EMPTY10		= 0x0d,	/* empty */
	EMPTY11		= 0x0e,	/* empty */
	EMPTY12		= 0x0f,	/* empty */
	EMPTY13		= 0x10,	/* empty */
	EMPTY14		= 0x11,	/* empty */
	EREVID		= 0x12,	/* Ethernet Revision ID (read-only) */
	EMPTY15		= 0x13,	/* empty */
	EMPTY16		= 0x14,	/* empty */
	ECOCON		= 0x15,	/* Clock Output Control Register */
	RESERVED10	= 0x16,	/* reserved */
	EFLOCON		= 0x17,	/* Ethernet Flow Control Register */
	EPAUSL		= 0x18,	/* Pause Timer Value Low Byte */
	EPAUSH		= 0x19	/* Pause Timer Value High Byte */
};

static void enc_spi_write(const uint8_t op, const uint8_t addr, const uint8_t data)
{
	uint8_t header;
	uint8_t payload;

	header = op << 5;
	header |= addr & 0x1f;
	payload = data;

	spi_send(header);
	spi_send(payload);
}

void enc28j60_init(void)
{
	/* receive buffer */

	/* set receive buffer start poitner (ERXST) */
	enc_spi_write(WCR, ERXSTL, 0);
	enc_spi_write(WCR, ERXSTH, 0);

	/* set receive buffer end pointer (ERXND) */
	enc_spi_write(WCR, ERXNDL, 0xf);
	enc_spi_write(WCR, ERXNDH, 0xff);

	/* set receive buffer read pointer (ERXRDPT) */
	enc_spi_write(WCR, ERXRDPTL, 0);
	enc_spi_write(WCR, ERXRDPTH, 0);

	/* transmit buffer */
	/* receive filters (ERXFCON) */

	/* poll ESTAT.CLKRDY bit */

	/* configure MAC registers */
	/* configure PHY registers */
}
