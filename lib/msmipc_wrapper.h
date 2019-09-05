#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <linux/types.h>

//#define AF_QIPCRTR 99

#define QRTR_NODE_BCAST	0xffffffffu
#define QRTR_PORT_CTRL	0xfffffffeu

struct sockaddr_qrtr {
	__kernel_sa_family_t sq_family;
	__u32 sq_node;
	__u32 sq_port;
};

enum qrtr_pkt_type {
	QRTR_TYPE_DATA		= 1,
	QRTR_TYPE_HELLO		= 2,
	QRTR_TYPE_BYE		= 3,
	QRTR_TYPE_NEW_SERVER	= 4,
	QRTR_TYPE_DEL_SERVER	= 5,
	QRTR_TYPE_DEL_CLIENT	= 6,
	QRTR_TYPE_RESUME_TX	= 7,
	QRTR_TYPE_EXIT          = 8,
	QRTR_TYPE_PING          = 9,
	QRTR_TYPE_NEW_LOOKUP	= 10,
	QRTR_TYPE_DEL_LOOKUP	= 11,
};

struct qrtr_ctrl_pkt {
	__le32 cmd;

	union {
		struct {
			__le32 service;
			__le32 instance;
			__le32 node;
			__le32 port;
		} server;

		struct {
			__le32 node;
			__le32 port;
		} client;
	};
} __packed;




int socket_qrtr(int domain, int type, int protocol);
int bind_qrtr(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int getsockname_qrtr(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
ssize_t sendto_qrtr(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom_qrtr(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
