#include "qtopia-ping.h"

#include <qapplication.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qmultilineedit.h>

#include <qfile.h>
#include <qmessagebox.h>
#include <qtopia/qcopenvelope_qws.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

TMainForm::TMainForm( QWidget * parent, const char * name, WFlags fl ) 
	: TMainFormBase(parent, name, fl)
{
//	qWarning("Richard TEST: %s, %d", "192.168.0.1", 68);
	init_function();
	ip_address->setText(QString("192.168.0.1"));
	receive_statistics->setText(QString(""));

	// signals and slots connections
	connect( StartButton, SIGNAL( clicked() ), this, SLOT( startButtonClicked() ) );
	connect( CloseButton, SIGNAL( clicked() ), this, SLOT( closeButtonClicked() ) );
}

void TMainForm::closeButtonClicked()
{
	close();
	return ;
}

void TMainForm::startButtonClicked()
{
	receive_statistics->setText(QString(""));

	ping();
	return ;
}

void TMainForm::init_function()
{
	addr =NULL;
	send_ip_addr =NULL;
	recv_ip_addr =NULL;
	sockfd =0;
	datalen = 56;

}

int TMainForm::ping()
{
	struct hostent *host;
	struct protoent *protocol;
	int size = 50 * 1024;
	addr = (char *)ip_address->text().latin1();
	
	//没有hostname或者ip地址
	if (ip_address->text().isEmpty()) {
		receive_statistics->insert(QString("usage:ping <hostname|ip_address>.\n"));
		return 1;
	}

	//不是ICMP协议
	if((protocol = getprotobyname("icmp")) == NULL) {
		receive_statistics->insert(QString("ERROR: getprotoibyname !\n"));
		return 1;
	}

	//生成使用ICMP的原始套接字，只有root才能生成
	if((sockfd = socket(AF_INET,SOCK_RAW,protocol->p_proto)) < 0) {
		receive_statistics->insert(QString("ERROR: socket error !\n"));
		return 1;
	}

	//回收root权限，设置当前权限
	setuid(getuid());

	/*扩大套接字的接收缓存区导50K，这样做是为了减小接收缓存区溢出的
	  可能性，若无意中ping一个广播地址或多播地址，将会引来大量的应答*/
	setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
	bzero(&dest_addr,sizeof(dest_addr));	//初始化
	dest_addr.sin_family = AF_INET;		//套接字域是AF_INET(网络套接字)

	//判断主机名是否是IP地址
	if( (inet_addr(ip_address->text().latin1())) == INADDR_NONE) {
		if((host = gethostbyname(ip_address->text().latin1())) == NULL)	{ //是主机名
			receive_statistics->insert(QString("ERROR: gethostbyname error !\n"));
			return 1;
		}
		memcpy((char *)&dest_addr.sin_addr,host->h_addr,host->h_length);

	} else { //是IP 地址
		dest_addr.sin_addr.s_addr = inet_addr( ip_address->text().latin1() );
	}
	pid = getpid();

//输出显示
	send_ip_addr = inet_ntoa(dest_addr.sin_addr);
	qWarning("PING %s (%s) %d(%d) bytes of data.\n", addr, 
			send_ip_addr, datalen, datalen+IP_HEAD_LEN+ICMP_LEN);

	receive_statistics->insert(QString("PING "));
	receive_statistics->insert(QString(addr));
	receive_statistics->insert(QString(" ("));
	receive_statistics->insert(QString(send_ip_addr));
	receive_statistics->insert(QString(") "));
	receive_statistics->insert(QString::number(datalen));
	receive_statistics->insert(QString("("));
	receive_statistics->insert(QString::number(datalen+IP_HEAD_LEN+ICMP_LEN));
	receive_statistics->insert(QString(") bytes of data.\n"));

	// 1. 发送
	send_packet();
	// 2. 接收
	recv_packet();

	return 0;
}


/////////////////send///////////////////

/****检验和算法****/
unsigned short TMainForm::cal_chksum(unsigned short *addr,int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short check_sum = 0;

	while(nleft>1)		//ICMP包头以字（2字节）为单位累加
	{
		sum += *w++;
		nleft -= 2;
	}

	if(nleft == 1)		//ICMP为奇数字节时，转换最后一个字节，继续累加
	{
		*(unsigned char *)(&check_sum) = *(unsigned char *)w;
		sum += check_sum;
	}
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	check_sum = ~sum;	//取反得到校验和
	return check_sum;
}

/*设置ICMP报头*/
int TMainForm::pack(int pack_no)
{
	int packsize;
	struct icmp *icmp;
	struct timeval *tval;
	icmp = (struct icmp*)sendpacket;
	icmp->icmp_type = ICMP_ECHO;	//ICMP_ECHO类型的类型号为0
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = pack_no;	//发送的数据报编号
	icmp->icmp_id = pid;

	packsize = 8 + datalen;		//数据报大小为64字节
	tval = (struct timeval *)icmp->icmp_data;
	gettimeofday(tval,NULL);		//记录发送时间
	//校验算法
	icmp->icmp_cksum =  cal_chksum((unsigned short *)icmp,packsize);	
	return packsize;
}

/****发送三个ICMP报文****/
void TMainForm::send_packet()
{
	int packetsize;
	packetsize = pack(1);	//设置ICMP报头 nsend=1
		//发送数据报
	if( sendto(sockfd, sendpacket, packetsize, 0,
		(struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
			perror("sendto error");
	}

}

/////////////////receive///////////////////


void TMainForm::recv_packet()
{
	int n;
	socklen_t fromlen;

	fromlen=sizeof(from);
//	alarm(MAX_WAIT_TIME);
	if( (n = recvfrom(sockfd, recvpacket, sizeof(recvpacket), 0, (struct sockaddr *)&from, &fromlen)) < 0) {
		perror("recvfrom error");
	}
	recv_ip_addr = inet_ntoa(from.sin_addr);
	gettimeofday(&tvrecv,NULL);
	unpack(recvpacket,n);
}

/******剥去ICMP报头******/
int TMainForm::unpack(char *buf,int len)
{
	int iphdrlen;		//ip头长度
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	double rtt;


	ip = (struct ip *)buf;
	iphdrlen = ip->ip_hl << 2;	//求IP报文头长度，即IP报头长度乘4
	icmp = (struct icmp *)(buf + iphdrlen);	//越过IP头，指向ICMP报头
	len -= iphdrlen;	//ICMP报头及数据报的总长度
	if(len < 8)		//小于ICMP报头的长度则不合理
	{
		qWarning("ICMP packet\'s length is less than 8\n");
		receive_statistics->insert(QString("ICMP packet\'s length is less than 8\n"));
		return -1;
	}
	//确保所接收的是所发的ICMP的回应
	if((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid)) {
		tvsend = (struct timeval *)icmp->icmp_data;
		tv_sub(&tvrecv,tvsend);	//接收和发送的时间差
		//以毫秒为单位计算rtt
		rtt = tvrecv.tv_sec*1000 + tvrecv.tv_usec/1000;
		//显示相关的信息
		qWarning("%d bytes from %s(%s): icmp_seq=%u ttl=%d time=%.3f ms\n",
			len, addr, recv_ip_addr, icmp->icmp_seq, ip->ip_ttl, rtt);

		receive_statistics->insert(QString("\n"));
		receive_statistics->insert(QString::number(len));
		receive_statistics->insert(QString(" bytes from "));
		receive_statistics->insert(QString(addr));
		receive_statistics->insert(QString("("));
		receive_statistics->insert(QString(recv_ip_addr));
		receive_statistics->insert(QString("): icmp_seq="));
		receive_statistics->insert(QString::number(icmp->icmp_seq));
		receive_statistics->insert(QString(" ttl="));
		receive_statistics->insert(QString::number(ip->ip_ttl));
		receive_statistics->insert(QString(" time="));
		receive_statistics->insert(QString::number(rtt));
		receive_statistics->insert(QString(" ms\n"));

		qWarning("\n--- alive %s(%s) ---\n",  addr, recv_ip_addr);
		receive_statistics->insert(QString("\n--- alive "));
		receive_statistics->insert(QString(addr));
		receive_statistics->insert(QString("("));
		receive_statistics->insert(QString(recv_ip_addr));
		receive_statistics->insert(QString(") ---\n"));

	} else {

		qWarning("\n--- NOT alive %s(%s) ---\n",  addr, send_ip_addr);
		receive_statistics->insert(QString("\n--- NOT alive "));
		receive_statistics->insert(QString(addr));
		receive_statistics->insert(QString("("));
		receive_statistics->insert(QString(send_ip_addr));
		receive_statistics->insert(QString(") ---\n"));

		return -1;
	}

	return 0;
}


//两个timeval相减
void TMainForm::tv_sub(struct timeval *recvtime,struct timeval *sendtime)
{
	long sec = recvtime->tv_sec - sendtime->tv_sec;
	long usec = recvtime->tv_usec - sendtime->tv_usec;
	if(usec >= 0){
		recvtime->tv_sec = sec;
		recvtime->tv_usec = usec;
	}else{
		recvtime->tv_sec = sec - 1;
		recvtime->tv_usec = usec + 1000000;
	}
}


