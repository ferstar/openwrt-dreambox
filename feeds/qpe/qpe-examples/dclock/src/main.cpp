/****************************************************************************
** $Id: qt/examples/dclock/main.cpp   2.3.10   edited 2005-01-24 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "dclock.h"
#include <qtopia/qpeapplication.h>
//#include <qapplication.h>


int main( int argc, char **argv )
{
//    QApplication a( argc, argv );
    QPEApplication a( argc, argv );
    DigitalClock *clock = new DigitalClock;
    clock->resize( 170, 80 );
//    a.setMainWidget( clock );
    a.showMainWidget( clock );
    clock->setCaption("Qt Example - Digital Clock");
    clock->show();
    return a.exec();
}
