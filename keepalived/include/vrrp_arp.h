/*
 * Soft:        Keepalived is a failover program for the LVS project
 *              <www.linuxvirtualserver.org>. It monitor & manipulate
 *              a loadbalanced server pool using multi-layer checks.
 *
 * Part:        vrrp_arp.c include file.
 *
 * Version:     $Id: vrrp_arp.h,v 0.7.6 2002/11/20 21:34:18 acassen Exp $
 *
 * Author:      Alexandre Cassen, <acassen@linux-vs.org>
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *              See the GNU General Public License for more details.
 *              
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 */

#ifndef _VRRP_ARP_H
#define _VRRP_ARP_H

/* system includes */
#include <net/ethernet.h>
#include <net/if_arp.h>

/* local includes */
#include "vrrp.h"

/* local definitions */
#define ETHERNET_HW_LEN		6
#define IPPROTO_ADDR_LEN	4

/* types definition */
typedef struct _m_arphdr {
	unsigned short int ar_hrd;		/* Format of hardware address.  */
	unsigned short int ar_pro;		/* Format of protocol address.  */
	unsigned char ar_hln;			/* Length of hardware address.  */
	unsigned char ar_pln;			/* Length of protocol address.  */
	unsigned short int ar_op;		/* ARP opcode (command).  */

	/* Ethernet looks like this : This bit is variable sized however...  */
	unsigned char __ar_sha[ETH_ALEN];	/* Sender hardware address.  */
	unsigned char __ar_sip[4];		/* Sender IP address.  */
	unsigned char __ar_tha[ETH_ALEN];	/* Target hardware address.  */
	unsigned char __ar_tip[4];		/* Target IP address.  */
} m_arphdr;

/* prototypes */
extern int send_gratuitous_arp(vrrp_rt * vrrp, int addr);

#endif