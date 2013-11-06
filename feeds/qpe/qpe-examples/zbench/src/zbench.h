
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

#include <sys/time.h>
#include <unistd.h>
#include <qwidget.h>
#include <qmainwindow.h>
#include <qimage.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpe/qpetoolbar.h>		// qpe/
#include <qaction.h>
#include <qpe/qpemenubar.h>		// qpe/
#include <qslider.h>
#include <qpe/qlibrary.h>		// qpe/
#include <qdatetime.h>
#include <qpe/applnk.h>			// qpe/
#include <qdialog.h>
class QCheckBox;
class QPEMenuBar;


#define       CHAR_TEST_COUNT     13000               // Bench character
#define       DRAW_TEST_COUNT     6500                // Bench Draw 5000-->6500


#define       MAX_X_SIZE          240                 // ザウルス画面サイズ
#define       MAX_Y_SIZE          320                 // ザウルス画面サイズ
#define       CAPTION_Y_SIZE      18                  // ザウルス　タイトルサイズ
#define       DISP_Y_SIZE         MAX_Y_SIZE - CAPTION_Y_SIZE - 1


class AppZBench : public QMainWindow
{
    Q_OBJECT
public:
    AppZBench( QWidget *parent=0, const char *name=0, int wFlags=0 );
    ~AppZBench();

	bool		which_int;
	bool		which_float;
	bool		which_text;
	bool		which_graphic;
	bool		which_main;
	bool		which_sd;
	bool		which_cf;

	bool		which_clipb;

private:
	QPEMenuBar	*menuBar;
	QPopupMenu	*popStart;
	QPushButton	*PushB;

	int			x_size;		// flame size
	int			y_size;		// flame size

	int			t1;
	int			t2;
	int			t3;
	int			t4;

	int			t5;			// main read
	int			t6;			// main write
	int			t7;			// sd read
	int			t8;			// sd write
	int			t9;			// cf read
	int			t10;		// cf write

	bool		main_rd;
	bool		main_wt;
	bool		sd_rd;
	bool		sd_wt;
	bool		cf_rd;
	bool		cf_wt;

	QClipboard	*clb;

	QString		dt_buf;
	QString		buf;

	void	outputResult();
	void	paintChar( void );
	void	paintLineRect( void );
	bool	writeFile( QString );
	bool	readFile( QString );

private slots:
	void	start_dialog( void );
	void	start_bench( void );

signals:
};


class StartDialog : public QDialog
{
    Q_OBJECT

	public:
		StartDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
		~StartDialog();

		int			x_size;		// flame size
		int			y_size;		// flame size

		bool		which_int;
		bool		which_float;
		bool		which_text;
		bool		which_graphic;
		bool		which_main;
		bool		which_sd;
		bool		which_cf;

		bool		which_clipb;

	private:

		AppZBench	*parent_app;

		QCheckBox *	IntCheckBox;
		QCheckBox *	FloatCheckBox;
		QCheckBox *	TextCheckBox;
		QCheckBox *	GraphicCheckBox;
		QCheckBox *	mainCheckBox;
		QCheckBox *	SdCheckBox;
		QCheckBox *	CfCheckBox;
		QCheckBox *	ClipbCheckBox;
		QPushButton *	PushButton1;
		QPushButton *	PushButton2;

	protected slots:
		void accept();

	public slots:
};
