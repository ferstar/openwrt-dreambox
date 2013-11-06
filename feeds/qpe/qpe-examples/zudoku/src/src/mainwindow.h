#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef QTOPIA_1_5
#include<qapplication.h>
typedef QApplication QPEApplication;
#else
#include<qtopia/qpeapplication.h>
#include <qtopia/qpemenubar.h>
#endif

#ifdef Q_WS_X11
#include <cstdlib>
#endif

#ifdef Q_WS_MACX
#include <cstdlib>
#include <qmessagebox.h>
#endif

#include <qwidgetstack.h>
#include <qdialog.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qmessagebox.h>
#include <qbuttongroup.h>
#include <qpopupmenu.h>
#include <qlabel.h>
#include <qframe.h>
#include <qhbox.h>
#include <qvbox.h>
#include <qsizepolicy.h>
#include <qapplication.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <qfile.h>
#include <qtextbrowser.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qabstractlayout.h>
#include <qimage.h>

#include "zudokuengine.h"

const int workTime = 10; // number of milliseconds to wait before next step of solve or generate

#ifdef QT_WIN
const QString helpFile = "zudoku.html";
const QString advertStem = "figadvert";
const QString saveFile = "zudokusavegame.txt";
const QString iconFile = "zudoku32x32.png";
#else
#ifdef QTOPIA_1_5
const QString helpFile = "/home/QtPalmtop/help/en/html/zudoku.html";
const QString advertStem = "/home/QtPalmtop/pics/figadvert";
const QString saveFile = "/home/zaurus/Documents/zudokusavegame.txt";
const QString iconFile = "/home/QtPalmtop/pics/zudoku.png";
#else
#ifdef Q_WS_MACX
#include <CFBundle.h>
QString getMacBundlePath();

const QString macBundle = getMacBundlePath();
const QString helpFile = macBundle + "/Contents/Resources/zudoku.html";
const QString advertStem = macBundle + "/Contents/Resources/figadvert";
const QString saveFile = QString(getenv("HOME"))+"/zudokusavegame.txt";
const QString iconFile = macBundle + "/Contents/Resources/zudoku32x32.png";
#else // X11
const QString helpFile = "/usr/share/doc/zudoku/html/zudoku.html";
const QString advertStem = "/usr/share/pixmaps/figadvert";
const QString saveFile = QString(getenv("HOME"))+"/zudokusavegame.txt";
const QString iconFile = "/usr/share/icons/hicolor/32x32/apps/zudoku.png";
#endif // not Mac

#endif // not Qtopia

#endif // not windows

const QString advertUrl = "http://www.figlabs.com/crm/campaign_tracker.php?track=11";
const QString tileFontName = "Helvetica";

// Dimensions in pixels - varies on different platforms
class ZDim {
public:
	static int tileScreenSize() { return hiRes() ? 40 : (portrait() ? 23 : 18); }
	static int tilePrintSize()	{ return 60; }
	static int labelFontSize()
	{
#ifdef QT_WIN
		return 200;
#else
		return hiRes() ? 20 : 12;
#endif
	}
	static int tileFontSize()
	{
#ifdef QT_WIN
		return 400;
#else
		return hiRes() ? 39 : (portrait() ? 22 : 17);
#endif
	}
	static int tileFontSmall()
	{
#ifdef QT_WIN
		return 150;
#else
		return hiRes() ? 12 : (portrait() ? 7 : 3);
#endif
	}
	static bool hiRes()
	{
		int resFactor = QApplication::desktop()->width() + QApplication::desktop()->height();
		return resFactor > 900;
	}
	static bool portrait()
	{
		return QApplication::desktop()->width() < QApplication::desktop()->height();
	}
};

class OpenLink {
public:
    /*!
     * \brief Open the specified URL.  This will attempt to open
     *  the specified url in the user's favourite browser using
     *  operating-system dependent techniques.  It is theorised
     *  that files could be opened, at least on the Windows
     *  platform, using this code without any modifications.
     */
    static const bool open(QWidget *widget, const QString &filename);
};

class CZudokuTile : public QPushButton
{
	Q_OBJECT
public:
	CZudokuTile( QWidget* parent) : QPushButton(parent) {}
	~CZudokuTile() { printf("~CZudokuTile\n");}
signals:
	void pressed(CZudokuTile* aTile, QChar aKey);
	void pressedMove(int aKey);
protected:
	virtual void keyPressEvent ( QKeyEvent * e )
	{
		QChar val = e->text()[0];
		if ((val>='1' && val<='9') || val==' ')
			emit pressed(this,val);
		else
		{
			int k = e->key(); 
			if (k==Qt::Key_Left || k==Qt::Key_Right || k==Qt::Key_Up || k==Qt::Key_Down )
			{
				emit pressedMove(k);
			}
			else
				e->ignore();
		}
	}
};

class CZudokuBoard : public QFrame
{
	Q_OBJECT
public:
	CZudokuBoard( QWidget* parent);
	~CZudokuBoard();

	void drawSquare(int x, int y, const QString& aText, QColor aColor, QFont aFont);
	void setBoardColor(QColor aColor) { setBackgroundColor(aColor); }
	QChar popup(int x, int y);

public slots:
	void onClick(int id);
	void onKey(CZudokuTile* aTile, QChar aKey);
	void onKeyMove(int aKey);
	
signals:
	void onClick(int x, int y);
	void onKey(QChar aKey,int x, int y);
		
private:
	QGridLayout* m_boardLayout;
	QPopupMenu* m_popup;
	QButtonGroup* m_bg;
	void setButtonColor(int butId, QColor aColor);
};

class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow( QWidget* parent);
	~CMainWindow();

public slots:
	void onClick(int x, int y);
	void onKey(QChar aKey,int x, int y);
	void onGenerate();
	void onSolve();
	void onTogglePossibles();
	void onTogglePencilMarks();
	void onSetBoard();
	void onPlay();
	void onPrint();
	void onAdvert();
	void onClear();
	void onHelp();
	void onCloseHelp();
	void onExit();
	void onRating(int aRating);
	void accept() { onExit(); }
	void reject() { onExit(); }
protected:
	virtual void timerEvent(QTimerEvent*);
	virtual void resizeEvent ( QResizeEvent * e) ;
#ifndef QTOPIA_1_5
	virtual void closeEvent ( QCloseEvent * e );
#endif
private:
	void displayBoard();
	void displaySquare(int x, int y, QPainter* printer=NULL, int px=0, int py=0);
	void showDifficulty();
	void doMove(QChar aP, int x, int y);
	void doOpen(const QString& aFile);
	void doSave(const QString& aFile);
	void showWorkingDifficulty(ZudokuLevel level);
	void showFinalDifficulty(ZudokuLevel level);
	QString ratingFromLevel(ZudokuLevel level);
	void updateRatingChecks();
	QString slurp(const QString& aFile);
	void showNextAdvert();
	bool okToProceed(const QString& warning);
	void doGenerate();
	QString doFormatSmallNumbers(QString poss);

	QWidgetStack* m_stack;
	QFrame* m_wholeFrame;
	QGridLayout* m_wholeLayout;
	CZudokuBoard* m_board;
	QLabel* m_info;
	QPopupMenu *m_file;
	QPopupMenu *m_game;
	QPopupMenu *m_help;
	QPopupMenu *m_rating;
	QVBox *m_helpWin;
	QTextBrowser *m_helpBrowser;
	QPushButton *m_closeHelp;
	QSpacerItem* m_sp1;
	QSpacerItem* m_sp2;
#ifndef QTOPIA_1_5
	QMenuBar* m_menuBar;
	QPtrList<QPixmap> m_adverts;
	QPushButton *m_advertBut;
#else
	QPEMenuBar* m_menuBar;
#endif

	int m_designItem;
	int m_solveItem;
	int m_possItem;
	int m_generateItem;
	int m_pencilItem;
	int m_trivItem,m_easyItem,m_mediItem,m_diffItem,m_fienItem,m_unlmItem;
	unsigned m_currentAdvert;
	int m_advertTimer;
	int m_workTimer;
	double m_printScaleFactor;	
	
	bool m_settingBoard;
	bool m_solving;
	bool m_generating;
	bool m_showPossibles;
	bool m_pencilMode;
	CZudokuEngine* m_engine;
	ZudokuLevel m_desiredRating;
};

#endif // MAINWINDOW_H
 
