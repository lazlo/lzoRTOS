#ifndef D_ENC28J60_H
#define D_ENC28J60_H

void enc28j60_init(unsigned char hwaddr[6],
		const unsigned short framelen,
		const unsigned char fd);

void enc28j60_ifup(void);

void enc28j60_ifdown(void);

void enc28j60_update(void);

#endif /* D_ENC28J60_H */
