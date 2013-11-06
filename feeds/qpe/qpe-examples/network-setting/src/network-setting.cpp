#include "network-setting.h"

#include <qpushbutton.h>
#include <qlineedit.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void TMainForm::closeButtonClicked()
{
	close();
	return ;
}

void TMainForm::saveButtonClicked()
{
	return ;
}

/*
* using the following cammonds to set network.
*
* 1. ifconfig eth0 down
* 2. ifconfig eth0 hw ether AA:BB:CC:DD:EE:FF
* 3. ifconfig eth0 192.168.0.2 netmask 255.255.255.0 up
* 4. route add default gw 192.168.0.1 
*/

void TMainForm::okButtonClicked()
{
	char hwaddr_cmd[50]="ifconfig eth0 hw ether ";
	char ip_netmask_cmd[100]="ifconfig eth0 ";
	char gateway_cmd[50]="route add default gw ";

	// MAC
	strncat(hwaddr_cmd, mac_data->text().latin1(), 17);
	qWarning("CAMMOND: ifconfig eth0 down");
	qWarning("CAMMOND: %s", hwaddr_cmd);

	// IP and netmask
	strcat(ip_netmask_cmd, ip_data->text().latin1());
	strcat(ip_netmask_cmd, " netmask ");
	strcat(ip_netmask_cmd, mask_data->text().latin1());
	strcat(ip_netmask_cmd, " up");
	qWarning("CAMMOND: %s", ip_netmask_cmd);

	// gateway
	strcat(gateway_cmd, gateway_data->text().latin1());
	qWarning("CAMMOND: %s", gateway_cmd);
	
//	system("ifconfig eth0 down");
//	system( hwaddr_cmd );
	system( ip_netmask_cmd );
	system( gateway_cmd );
	
	return ;
}

TMainForm::TMainForm( QWidget * parent, const char * name, WFlags fl ) 
	: TMainFormBase(parent, name, fl)
{
	ip_data->setText(QString("192.168.0.101")); //应该先读取系统上的ip，netmask，gateway，dns
	mask_data->setText(QString("255.255.255.0"));
	gateway_data->setText(QString("192.168.0.1"));
	dns_data->setText(QString("192.168.0.1"));
	mac_data->setText(QString( read_hwaddr() ));

	// signals and slots connections
	connect( SaveButton, SIGNAL( clicked() ), this, SLOT( saveButtonClicked() ) );
	connect( CloseButton, SIGNAL( clicked() ), this, SLOT( closeButtonClicked() ) );
	connect( OKButton, SIGNAL( clicked() ), this, SLOT( okButtonClicked() ) );
}

char * TMainForm::read_hwaddr()
{
	FILE *file=fopen("/sys/class/net/eth0/address","r");
	if (!file) {
		perror("fopen\n");
		return NULL;
	}
	if (fgets(hwaddr, 18, file)) {
		qWarning("HWaddr(MAC): %s", hwaddr);
	}
	fclose(file);
	return hwaddr;
}
