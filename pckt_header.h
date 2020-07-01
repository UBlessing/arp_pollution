struct ether_addr {
	unsigned char addr[6];
}__attribute__((packed));
typedef struct ether_addr ETHER_ADDR;

//사용 안함
struct ip_addr {
	unsigned int addr;
}__attribute__((packed));
typedef struct ip_addr IP_ADDR;
//////

struct ether_header {
	ETHER_ADDR dst;
	ETHER_ADDR src;
	unsigned short type;
	/*
	 * ether types:
	 * 	0x0800 is IP
	 * 	0x86DD is IPv6
	 * 	0x8191 is NetBIOS
	 * 	0x0600 is Xerox XNS IDP
	 * 	0x0805 is X.25
	 * 	0x0806 is ARP
	 * 	0x0835 is RARP
	 * 	0x6003 is DEC DECnet Phase IV
	 * 	0x8137 is Novell Netware IPX
	 * 	0x8847 is MPLS
	 * 	0x8863 is PPPoE Discovery Stage
	 * 	0x8864 is PPPoE PPP Session Stage
	 */
}__attribute__((packed));
typedef struct ether_header ETHER_HEADER;

struct arp_header {
	unsigned short hardw_type; //hardware type
	unsigned short proto_type; //porotocol type
	unsigned char hard_addr_len; //hardware address len
	unsigned char proto_addr_len; //protocal address len
	unsigned short opcode; //operation code
	ETHER_ADDR src_mac_addr;
	unsigned int src_addr;
	ETHER_ADDR dst_mac_addr;
	unsigned int dst_addr;
	/* protocol_type same ether_types.
	 * if mac addr is "ff:ff:ff:ff:ff:ff", it is broadcast.
	 * operation code:
	 * 	1 is Arp Request
	 * 	2 is Arp Reply
	 * 	3 is Rarp Request
	 * 	4 is Rarp Reply
	 */
}__attribute__((packed));
typedef struct arp_header ARP_HEADER;

struct arp_packet {
	ETHER_HEADER ether_hdr;
	ARP_HEADER arp_hdr;
}__attribute__((packed));
typedef struct arp_packet ARP_PACKET;
