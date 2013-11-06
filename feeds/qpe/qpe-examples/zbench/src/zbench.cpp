// zbench.cpp
// ******************************************************************
// Benchmark v1.0
// 1. Integer
// 2. Floatingpoint
// 3. Draw character
// 4. Draw graphic( line & rect )
// ******************************************************************

// ******************************************************************
// Copyright (c) 2002- Satoshi, All Rights Reserved.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//
// Author : Satoshi ( af230533@im07.alpha-net.ne.jp )
// ******************************************************************

// #include "qpe/resource.h"		// qpe/

// #include <qmenubar.h>
#include <qwidgetstack.h>
// #include <qpe/qpetoolbar.h>		// qpe/
#include <qaction.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpe/qpemenubar.h>
#include <qpopupmenu.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qkeycode.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qclipboard.h>
#include <qtimer.h>
#include <qsizepolicy.h>
#include <qpe/qpeapplication.h>		// qpe/
#include <qpe/qcopenvelope_qws.h>	// qpe/
//#include <qpe/qpedecoration_qws.h>	// qpe/
#include <qpe/config.h>
#include <qcolor.h>
#include <qclipboard.h>
#include <qdialog.h>
#include <qcheckbox.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "zbench.h"

extern "C" { void   BenchFFT( void ); }
extern "C" { void   BenchInteger( void ); }
//===========================================================================

AppZBench::AppZBench( QWidget *parent, const char *name, int wFlags )
    : QMainWindow( parent, name, wFlags )
{
    popStart = new QPopupMenu( this );

	QAction *a = new QAction( tr( "&Setting" ), QString::null, Key_S + CTRL, this, 0 );
	connect( a, SIGNAL( activated() ), this, SLOT( start_dialog() ) );
	a->addTo( popStart );

    menuBar  = new QPEMenuBar( this );
	menuBar->insertItem( tr( "Start" ), popStart );

	PushB = new QPushButton( " ZBench START ! ", this );
	connect( PushB, SIGNAL( clicked() ), this, SLOT( start_bench() ) );
	PushB->hide();

    setCaption( tr("[ ZBench ] benchmark test program v2.0") );

	which_int     = true;
	which_float   = true;
	which_text    = true;
	which_graphic = true;
	which_main    = false;
	which_sd      = false;
	which_cf      = false;
	which_clipb   = true;
}

AppZBench::~AppZBench()
{
}



// **********************************************************************
// Start ZBench
// **********************************************************************
void AppZBench::start_dialog( void )
{
	StartDialog stDialog( this, "startdialog", true, 0 );
	if ( stDialog.exec() == QDialog::Accepted )
	{
		x_size = stDialog.x_size;
		y_size = stDialog.y_size;

		which_int     = stDialog.which_int;
		which_float   = stDialog.which_float;
		which_text    = stDialog.which_text;
		which_graphic = stDialog.which_graphic; 
		which_main    = stDialog.which_main;
		which_sd      = stDialog.which_sd;
		which_cf      = stDialog.which_cf;

		which_clipb   = stDialog.which_clipb;
	}
	PushB->setGeometry( ( x_size - 200 )/ 2, y_size / 2 - 70, 200, 50 );
	PushB->show();
}
void AppZBench::start_bench( void )
{
	QTime		t;
	char		*msg1 = "Don't touch the window!";
	char		*msg2 = "Please wait a minute.";
	QString		main_file = "/home/zaurus/ZBench.dat";
	QString		sd_file = "/var/mnt/card/ZBench.dat";
	QString		cf_file = "/var/mnt/cf/ZBench.dat";
	QPainter    pt;

	PushB->hide();

		// **********************************
		// start !!!
		// **********************************
		//----------------------------------- message
		pt.begin( this );
		pt.setPen( QColor( 255, 0, 0 ));
		pt.drawText( ( x_size - strlen( msg1 )*10 )/ 2, y_size / 2 + 30, msg1, strlen( msg1 ) );
		pt.drawText( ( x_size - strlen( msg2 )*10 )/ 2, y_size / 2 + 70, msg2, strlen( msg2 ) );
		pt.end();

		// ---------------------------------- Integer
		if ( which_int )
		{
			t.start();
			BenchInteger();
			t1 = t.elapsed();
		}

		// ---------------------------------- FFT
		if ( which_float )
		{
			t.start();
			BenchFFT();
			t2 = t.elapsed();
		}


		// ---------------------------------- main read & write File	v2.0.0
		if ( which_main )
		{
			t.start();
			main_wt = writeFile( main_file );
			t6 = t.elapsed();

			t.start();
			main_rd = readFile( main_file );
			t5 = t.elapsed();

			QFile	mainFile( main_file );
			mainFile.remove();
		}

		// ---------------------------------- sd read & write File	v2.0.0
		if ( which_sd )
		{
			t.start();
			sd_wt = writeFile( sd_file );
			t8 = t.elapsed();

			t.start();
			sd_rd = readFile( sd_file );
			t7 = t.elapsed();

			QFile	sdFile( sd_file );
			sdFile.remove();
		}

		// ---------------------------------- cf read & write File	v2.0.0
		if ( which_cf )
		{
			t.start();
			cf_wt = writeFile( cf_file );
			t10 = t.elapsed();

			t.start();
			cf_rd = readFile( cf_file );
			t9 = t.elapsed();

			QFile	cfFile( cf_file );
			cfFile.remove();
		}

		// ---------------------------------- draw Char
		if ( which_text )
		{
			t.start();
			paintChar();
			t3 = t.elapsed();
		}

		// ---------------------------------- draw Graphic
		if ( which_graphic )
		{
			t.start();
			paintLineRect();
			t4 = t.elapsed();
		}

		// ---------------------------------- end
		QTime	tt;
		QDate	dd;
		QString buf1;
		QString buf2;
		QString buf3;
		QString buf4;
		QString buf5;
		QString buf6;
		QString buf7;
		QString buf8;
		QString buf9;
		QString buf10;

		tt = QTime::currentTime();
		dd = QDate::currentDate();
		dt_buf.sprintf( "- %04d.%02d.%02d %02d:%02d:%02d -\n", dd.year(), dd.month(), dd.day(), tt.hour(), tt.minute(), tt.second() );

		if ( which_int )
			buf1.sprintf( "[    Integer     ] time is %2d.%03d sec\n", t1/1000, t1%1000 );
		if ( which_float )
			buf2.sprintf( "[ Floating point ] time is %2d.%03d sec\n", t2/1000, t2%1000 );
		if ( which_text )
			buf3.sprintf( "[   Draw Text    ] time is %2d.%03d sec\n", t3/1000, t3%1000 );
		if ( which_graphic )
			buf4.sprintf( "[  Draw Graphic  ] time is %2d.%03d sec\n", t4/1000, t4%1000 );

		if ( which_main )
		{
			if ( main_rd )
				buf5.sprintf( "[ main unit ] read time is %2d.%03d sec\n", t5/1000, t5%1000 );
			else
				buf5.sprintf( "[ main unit ] read error!\n" );
			if ( main_wt )
				buf6.sprintf( "             write time is %2d.%03d sec\n", t6/1000, t6%1000 );
			else
				buf6.sprintf( "             write error!\n" );
		}

		if ( which_sd )
		{
			if ( sd_rd )
				buf7.sprintf( "[ SD card ]   read time is %2d.%03d sec\n", t7/1000, t7%1000 );
			else
				buf7.sprintf( "[ SD card ]   read error!\n" );
			if ( sd_wt )
				buf8.sprintf( "             write time is %2d.%03d sec\n", t8/1000, t8%1000 );
			else
				buf8.sprintf( "             write error!\n" );
		}

		if ( which_cf )
		{
			if ( cf_rd )
				buf9.sprintf( "[ CF card ]   read time is %2d.%03d sec\n", t9/1000, t9%1000 );
			else
				buf9.sprintf( "[ CF card ]   read error!\n" );
			if ( cf_wt )
				buf10.sprintf( "             write time is %2d.%03d sec\n", t10/1000, t10%1000 );
			else
				buf10.sprintf( "             write error!\n" );
		}

		buf = buf1 + buf2 + buf3 + buf4 + buf5 + buf6 + buf7 + buf8 + buf9 + buf10;
/*------
		sprintf( buf, "Integer time is %d.%03d sec\nFloating point time is %d.%03d sec\nDraw Text time is %d.%03d sec\nDraw Graphic time is %d.%03d sec",
 	 					t1/1000, t1%1000,
 	 					t2/1000, t2%1000,
 	 					t3/1000, t3%1000,
 	 					t4/1000, t4%1000 );
------*/
		if ( buf.length() > 0 )
		{
			outputResult();
			QMessageBox::information( this, tr("- ZBench - result time"), tr( buf ));
		}
		else
		{
			QMessageBox::information( this, tr("- ZBench - result time"), tr( "nothing !!!" ));
		}

		if (( which_clipb ) && ( buf.length() > 0 ))
		{
			clb = QApplication::clipboard();
			clb->setText( dt_buf + buf );
		}

//	PushB->show();
	close();
}


// **********************************************************************
// Darw Text
// **********************************************************************
void AppZBench::outputResult()
{
	QString		out_file = "/home/zaurus/Documents/Text_Files/ZBench_result.txt";

	QFile	writeFile( out_file );

	if ( buf.length() > 0 )
	{
//		if ( writeFile.open( IO_Append ))	// IO_Append can't use ???
/*----
		if ( writeFile.open( IO_WriteOnly ))
		{
//			QTextStream		stream( &writeFile );
//			stream << dt_buf + buf + "\n";

			writeFile.writeBlock( r_buf, r_buf.length() );
			writeFile.writeBlock( dt_buf, dt_buf.length() );
			writeFile.writeBlock( buf + "\n", buf.length() + 1 );

			writeFile.close();
		}
------*/
			FILE	*fp;

			if (( fp = fopen( out_file, "at" )) != NULL )
			{
				fputs( dt_buf, fp );
				fputs( buf, fp );
				fputs( "\n", fp );
				fclose( fp );
			}
	}
}

// **********************************************************************
// Darw Text
// **********************************************************************
void AppZBench::paintChar()
{
	int         i;
	int         k;
	int			rr[] = { 255, 255, 255,   0,   0,   0,   0, 128, 128 };
	int			gg[] = {   0, 255,   0,   0, 255, 255,   0, 128, 128 };
	int			bb[] = {   0,   0, 255,   0,   0, 255, 255, 128,   0 };
	int         xx;
	int         yy;
	char       *wk = "ZaurusBenchTest";
	QPainter    pt;

	srand( time( NULL ) );
	pt.begin( this );

	for ( i= 0 ; i < CHAR_TEST_COUNT ; i++ )
	{
		k = rand() % 9;
		pt.setPen( QColor( rr[k], gg[k], bb[k] ));

		xx = rand() % ( x_size - 100 );
		yy = rand() % ( y_size - CAPTION_Y_SIZE - 1 ) + CAPTION_Y_SIZE;

		pt.drawText( xx, yy, wk, 15 );
	}
	pt.end();
}

// **********************************************************************
// Draw Graphic
// **********************************************************************
// 2003.06.06 append  pt.drawArc( ...
// **********************************************************************
void AppZBench::paintLineRect()
{
	int         i;
	int         k;
	int			rr[] = { 255, 255, 255,   0,   0,   0,   0, 128, 128 };
	int			gg[] = {   0, 255,   0,   0, 255, 255,   0, 128, 128 };
	int			bb[] = {   0,   0, 255,   0,   0, 255, 255, 128,   0 };
	int         xx1;
	int         xx2;
	int         yy1;
	int         yy2;
	QPainter    pt;
	QBrush		br;

	srand( time( NULL ) );
	pt.begin( this );

	for ( i= 0 ; i < DRAW_TEST_COUNT ; i++ )
	{
		k = rand() % 9;
		pt.setPen( QColor( rr[k], gg[k], bb[k] ));

		xx1 = rand() % x_size;
		xx2 = rand() % x_size;
		yy1 = rand() % ( y_size - CAPTION_Y_SIZE - 1 ) + CAPTION_Y_SIZE;
		yy2 = rand() % ( y_size - CAPTION_Y_SIZE - 1 ) + CAPTION_Y_SIZE;

		pt.drawLine( xx1, yy1, xx2, yy2 );
	}
	br.setStyle( SolidPattern );
	for ( i= 0 ; i < DRAW_TEST_COUNT ; i++ )
	{
		k = rand() % 9;
		pt.setPen( QColor( rr[k], gg[k], bb[k] ));

		xx1 = rand() % ( x_size - 90 ) + 10;
		xx2 = rand() % 20 + 50;				// width
		yy1 = rand() % ( y_size - 70 ) + 24;
		yy2 = rand() % 10 + 40;				// hight

		pt.drawArc( xx1, yy1, xx2, yy2, 360*16, 360*16 ); 
	}
	for ( i= 0 ; i < DRAW_TEST_COUNT ; i++ )
	{
		k = rand() % 9;
		br.setColor( QColor( rr[k], gg[k], bb[k] ));

		xx1 = rand() % ( x_size - 90 ) + 10;
		xx2 = rand() % 20 + 50;				// width
		yy1 = rand() % ( y_size - 70 ) + 24;
		yy2 = rand() % 10 + 40;				// hight

		pt.fillRect( xx1, yy1, xx2, yy2, br );
	}
	pt.end();
}



// **********************************************************************
// Read & Write
// v2.0.0
// **********************************************************************
#define   BUFF_SIZE        8192
#define   FILE_SIZE        1024 * 1024		// 1Mb
char	  FileBuf[BUFF_SIZE+1];

bool AppZBench::writeFile( QString w_path )
{
	int		i;
	int		k;
	int		n;
	int		pos;
	int		len;
	char	*data = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	// 62


// /*------------------------------------
	int		w_len;

	QFile	writeFile( w_path );
	srand( time( NULL ) );

	for( n= 0 ; n < 20 ; n++ )
	{
		if ( ! writeFile.open( IO_WriteOnly ))
		{
			writeFile.close();
			writeFile.remove();
			return( false );
		}
		// ------------------------------------------ sequential write
        for( k= 0 ; k < 256 ; k++ )
		{
			n = rand() % 30;
			memcpy( &FileBuf[k*32], &data[n], 32 );
		}

		for( i= 0 ; i < FILE_SIZE / BUFF_SIZE ; i++ )
		{
			w_len = writeFile.writeBlock( FileBuf, BUFF_SIZE );
			if ( w_len != BUFF_SIZE )
			{
				writeFile.close();
				writeFile.remove();
				return( false );
			}
			writeFile.flush();
        }
		// ------------------------------------------ random write
		for( i= 0 ; i < 400 ; i++ )
        {
        	len = rand() % 90 + 4000;
        	for( k= 0 ; k < 128 ; k++ )
            {
				n = rand() % 30;
				memcpy( &FileBuf[k*8], &data[n], 32 );
            }
			pos = rand() % ( FILE_SIZE - BUFF_SIZE );

			writeFile.at( pos );
			w_len = writeFile.writeBlock( FileBuf, len );
			if ( w_len != len )
			{
				writeFile.close();
				writeFile.remove();
				return( false );
			}
			writeFile.flush();
        }
		writeFile.close();
	}
	return( true );
// ------------------------------------*/

/* ----------------------------------
	srand( time( NULL ) );

	FILE	*fp;

	for( n= 0 ; n < 40 ; n++ )
	{
		if (( fp = fopen( w_path, "wt" )) == NULL )
			return( false );
		memset( FileBuf, '\0', BUFF_SIZE+1 );
		// ------------------------------------------ sequential write
		for( i= 0 ; i < FILE_SIZE / BUFF_SIZE ; i++ )
        {
        	for( k= 0 ; k < 128 ; k++ )
            {
				n = rand() % 30;
				memcpy( &FileBuf[k*8], &data[n], 32 );
            }
			fputs( FileBuf, fp );
        }
		// ------------------------------------------ random write
		for( i= 0 ; i < 300 ; i++ )
        {
			memset( FileBuf, '\0', 130 );
        	len = rand() % 120 + 8;
        	for( k= 0 ; k < 16 ; k++ )
            {
				n = rand() % 54;
				memcpy( &FileBuf[k*8], &data[n], 8 );
            }
			pos = rand() % ( FILE_SIZE / BUFF_SIZE - BUFF_SIZE );

			fseek( fp, pos, SEEK_SET );
			fputs( FileBuf, fp );
        }
        fclose( fp );
	}
	return( true );
-------------------------------------*/
}


bool AppZBench::readFile( QString r_path )
{
	int		i;
	int		k;
	int		len;
	int		pos;
	int		r_len;

	QFile	readFile( r_path );
	srand( time( NULL ) );

	for( k= 0 ; k < 200 ; k++ )
	{
		if ( ! readFile.open( IO_ReadOnly ))
		{
			readFile.remove();
			return( false );
		}
		// ------------------------------------------ sequential read
        readFile.at( 0 );
		for( i= 0 ; i < FILE_SIZE / BUFF_SIZE ; i++ )
        {
        	readFile.at( i * BUFF_SIZE );
			r_len = readFile.readBlock( FileBuf, BUFF_SIZE );
			if ( r_len != BUFF_SIZE )
			{
				readFile.close();
				readFile.remove();
				return( false );
			}
		}
		// ------------------------------------------ random read
		for( i= 0 ; i < 1000 ; i++ )
        {
        	len = rand() % 120 + 8;
			pos = rand() % ( FILE_SIZE / BUFF_SIZE - BUFF_SIZE );
            readFile.at( pos );
			r_len = readFile.readBlock( FileBuf, len );
			if ( r_len != len )
			{
				readFile.close();
				readFile.remove();
				return( false );
			}
        }
		readFile.close();
	}
	return( true );
}



// **********************************************************************
// 
// v2.0.0
// **********************************************************************
StartDialog::StartDialog( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
	bool		c700 = false;
	int			xx;

	// ---------------------------------- frame size
	x_size = parent->width();
	y_size = parent->height();
	if ( x_size > 400 )			// check A300, B500 : 240 x 320 size is 2/3
	{							// 480x640, 640x480
		xx = 300;
		c700 = true;
	}
	else						// 240 x 320
	{
		xx = 200;
	}

	setCaption( tr( "ZBench start dialog" ) );

	QLabel* label1 = new QLabel( tr( "- [ ZBench ] user choice -" ), this );
	if ( c700 )
		label1->setGeometry( QRect( 5, 10, 300, 25 ) );
	else
		label1->setGeometry( QRect( 5, 10, 200, 17 ) );


	IntCheckBox     = new QCheckBox( tr( " Integer" ), this );
	if ( c700 )
		IntCheckBox->setGeometry( QRect( 8, 37, xx - 11, 25 ) );
	else
		IntCheckBox->setGeometry( QRect( 8, 29, xx - 11, 17 ) );

	FloatCheckBox   = new QCheckBox( tr( " Floating Point" ), this );
	if ( c700 )
		FloatCheckBox->setGeometry( QRect( 8, 64, xx - 11, 25 ) );
	else
		FloatCheckBox->setGeometry( QRect( 8, 48, xx - 11, 17 ) );

	TextCheckBox    = new QCheckBox( tr( " Draw Text" ), this );
	if ( c700 )
		TextCheckBox->setGeometry( QRect( 8, 91, xx - 11, 25 ) );
	else
		TextCheckBox->setGeometry( QRect( 8, 67, xx - 11, 17 ) );

	GraphicCheckBox = new QCheckBox( tr( " Draw Graphic" ), this );
	if ( c700 )
		GraphicCheckBox->setGeometry( QRect( 8, 118, xx - 11, 25 ) );
	else
		GraphicCheckBox->setGeometry( QRect( 8, 86, xx - 11, 17 ) );

	mainCheckBox    = new QCheckBox( tr( " main unit" ), this );
	if ( c700 )
		mainCheckBox->setGeometry( QRect( 8, 145, xx - 11, 25 ) );
	else
		mainCheckBox->setGeometry( QRect( 8, 105, xx - 11, 17 ) );

	SdCheckBox      = new QCheckBox( tr( " SD card" ), this );
	if ( c700 )
		SdCheckBox->setGeometry( QRect( 8, 172, xx - 11, 25 ) );
	else
		SdCheckBox->setGeometry( QRect( 8, 124, xx - 11, 17 ) );

	CfCheckBox      = new QCheckBox( tr( " CF card" ), this );
	if ( c700 )
		CfCheckBox->setGeometry( QRect( 8, 199, xx - 11, 25 ) );
	else
		CfCheckBox->setGeometry( QRect( 8, 143, xx - 11, 17 ) );



	QLabel* label2 = new QLabel( tr( "*** output result ***" ), this );
	if ( c700 )
		label2->setGeometry( QRect( 5, 226, xx - 11, 25 ) );
	else
		label2->setGeometry( QRect( 5, 162, xx - 11, 17 ) );
	ClipbCheckBox   = new QCheckBox( tr( " clipboard" ), this );
	if ( c700 )
		ClipbCheckBox->setGeometry( QRect( 8, 253, xx - 11, 25 ) );
	else
		ClipbCheckBox->setGeometry( QRect( 8, 181, xx - 11, 17 ) );



	PushButton1 = new QPushButton( tr( "OK" ), this );
	if ( c700 )
		PushButton1->setGeometry( QRect( 8, 280, 72, 26 ) );
	else
		PushButton1->setGeometry( QRect( 8, 200, 72, 26 ) );

	PushButton2 = new QPushButton( tr( "Cancel" ), this );
	if ( c700 )
		PushButton2->setGeometry( QRect( xx - 115, 280, 110, 26 ) );
	else
		PushButton2->setGeometry( QRect( xx - 115, 200, 110, 26 ) );

	connect( PushButton1 ,SIGNAL( clicked()), this, SLOT( accept()) );
	connect( PushButton2 ,SIGNAL( clicked()), this, SLOT( hide()) );

	// ------------------------------ default check
	IntCheckBox->setChecked( ((AppZBench*)parent)->which_int );
	FloatCheckBox->setChecked( ((AppZBench*)parent)->which_float );
	TextCheckBox->setChecked( ((AppZBench*)parent)->which_text );
	GraphicCheckBox->setChecked( ((AppZBench*)parent)->which_graphic );
	mainCheckBox->setChecked( ((AppZBench*)parent)->which_main );
	SdCheckBox->setChecked( ((AppZBench*)parent)->which_sd );
	CfCheckBox->setChecked( ((AppZBench*)parent)->which_cf );
	ClipbCheckBox->setChecked( ((AppZBench*)parent)->which_clipb );
}


void StartDialog::accept()
{
	which_int     = IntCheckBox->isChecked();
	which_float   = FloatCheckBox->isChecked();
	which_text    = TextCheckBox->isChecked();
	which_graphic = GraphicCheckBox->isChecked();
	which_main    = mainCheckBox->isChecked();
	which_sd      = SdCheckBox->isChecked();
	which_cf      = CfCheckBox->isChecked();
	which_clipb   = ClipbCheckBox->isChecked();
	hide();
	QDialog::accept();
}


/*
 *  Destroys the object and frees any allocated resources
 */
StartDialog::~StartDialog()
{
}

// eof
