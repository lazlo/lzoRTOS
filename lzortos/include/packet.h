#ifndef D_PACKET_H
#define D_PACKET_H

#define ETH_ALEN	6
#define ETH_HLEN	14

struct eth_addr {
	unsigned char addr[ETH_ALEN];
};

struct eth_hdr {
	struct eth_addr dst;
	struct eth_addr src;
	unsigned short type;
};

#endif /* D_PACKET_H */
