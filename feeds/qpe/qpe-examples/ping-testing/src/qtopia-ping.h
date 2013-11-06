#ifndef TMAINFORM_H
#define TMAINFORM_H

#include "qtopia-ping-base.h"
#include <qvariant.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/time.h>

#define	PACKET_SIZE	4096
#define	MAX_WAIT_TIME	5
#define	MAX_NO_PACKETS	10

#define IP_HEAD_LEN 20
#define ICMP_LEN 8



class TMainForm : public TMainFormBase
{
    Q_OBJECT

public:
    TMainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel);
    ~TMainForm() {}

public slots:
    void closeButtonClicked();
    void startButtonClicked();

protected:

protected slots:

private:
	int ping();
	void init_function();
	void send_packet();
	int pack(int pack_no);
	unsigned short cal_chksum(unsigned short *addr,int len);

	void tv_sub(struct timeval *recvtime,struct timeval *sendtime);
	int unpack(char *buf,int len);
	void recv_packet();

private:
	pid_t pid;
	int sockfd;
	char *addr;
	char *send_ip_addr;
	char *recv_ip_addr;
	char sendpacket[PACKET_SIZE];
	char recvpacket[PACKET_SIZE];
	int datalen;
	struct sockaddr_in dest_addr;
	struct sockaddr_in from;
	struct timeval tvrecv;

};

#endif // TMAINFORM_H
