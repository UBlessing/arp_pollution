#define mac_addr_size 6

struct ether_header {
	unsigned char ether_dst_mac[mac_addr_size];
	unsigned char ether_src_mac[mac_addr_size];
	unsigned short ether_type;
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
};

struct arp_header {
	unsigned short hardware_type;
	unsigned short protocol_type;
	unsigned char hard_addr_len;
	unsigned char proto_addr_len;
	unsigned short operation_code;
	unsigned char src_mac_addr[mac_addr_size];
	unsigned long src_addr;
	unsigned char dst_mac_addr[mac_addr_size];
	unsigned long dst_addr;
	/* protocol_type same ether_types.
	 * if mac addr is "ff:ff:ff:ff:ff:ff", it is broadcast.
	 * operation code:
	 * 	1 is Arp Request
	 * 	2 is Arp Reply
	 * 	3 is Rarp Request
	 * 	4 is Rarp Reply
	 */
};
