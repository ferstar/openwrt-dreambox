// main.cpp
// *********************************************************************
// ZBench
// Benchmark test for MI-Zaurus & SL-Zaurus
// *********************************************************************

#include <qpe/qpeapplication.h>
#include <qstring.h>
#include "zbench.h"


#include <stdio.h>

int main( int argc, char ** argv )
{
    QPEApplication app( argc, argv );

    AppZBench zb;
    app.showMainWidget( &zb );

    return app.exec();
}


