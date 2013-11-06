#include "title_language.h"

#include <qfile.h>
#include <qmessagebox.h>
#include <qtopia/qcopenvelope_qws.h>
#include <qtopia/qpeapplication.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void TMainForm::cancelButtonClicked()
{
	close();
	return ;
}

void TMainForm::chineseButtonClicked()
{
	LanguageName = CN;
	return ;
}

void TMainForm::englishButtonClicked()
{
	LanguageName = EN;
	return ;
}

void TMainForm::okButtonClicked()
{

	QMessageBox mb( tr("Language Setting"),
			tr("It will cause Qtopia to Restart\n"
			   " and Close all applications !\n"
			   "\n"
			   "       Change Language ?"),
			QMessageBox::NoIcon,
			QMessageBox::Yes | QMessageBox::Default,
			QMessageBox::No | QMessageBox::Escape,
			QMessageBox::NoButton );
	if ( mb.exec() == QMessageBox::Yes) {

		if (LanguageName == CN){
			qWarning("Chinese");
			qWarning(  ( "tar zxf "+QPEApplication::qpeDir()+"i18n/qtopia-titles/qtopia-titles-cn.tar.gz -C "+QPEApplication::qpeDir() ).latin1() );
			::system( ( "tar zxf "+QPEApplication::qpeDir()+"i18n/qtopia-titles/qtopia-titles-cn.tar.gz -C "+QPEApplication::qpeDir() ).latin1() );

		} else {
			qWarning("English");
			qWarning(  ( "tar zxf "+QPEApplication::qpeDir()+"i18n/qtopia-titles/qtopia-titles-en.tar.gz -C "+QPEApplication::qpeDir() ).latin1() );
			::system( ( "tar zxf "+QPEApplication::qpeDir()+"i18n/qtopia-titles/qtopia-titles-en.tar.gz -C "+QPEApplication::qpeDir() ).latin1() );

		}

		pid_t pid;
		if( (pid= ::fork()) > 0) exit(0);//是父进程，结束父进程
		else if(pid< 0) exit(1);//fork失败，退出

		/* 子进程成为新的会话组长和进程组长 */
		::setsid();

		QCopEnvelope e("QPE/System", "restart()" ); //restart qtopia
		qWarning("Restarting Qtopia ...");
	}

	return ;
}

