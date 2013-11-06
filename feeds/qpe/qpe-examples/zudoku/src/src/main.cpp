
#include <time.h>
#include "mainwindow.h"

int main( int argc, char ** argv )
{
	srand(time(NULL));
	QPEApplication a(argc,argv);
	CMainWindow* zudoku = new CMainWindow(NULL);
#ifndef QTOPIA_1_5
	zudoku->show();
#else
	a.showMainWidget(zudoku);
#endif	
	return a.exec();
}
