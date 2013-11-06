#include "mainwindow.h"

// ---------------------------------------------------------------------------------------
// The board widget

CZudokuBoard::CZudokuBoard( QWidget* parent )
    : QFrame( parent, "ZudokuBoard" )
{
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	m_boardLayout = new QGridLayout( this, 15,14,1 ); 
	setBackgroundColor(black);
    m_boardLayout->setSpacing( 1 );
    m_boardLayout->setMargin( 4 );
	m_bg = new QButtonGroup(this);
	m_bg->hide();
	QFont f(tileFontName, 12, QFont::Normal);
	f.setStyleHint(QFont::SansSerif);
	f.setPixelSize(ZDim::labelFontSize());
	m_popup = new QPopupMenu(this);
	m_popup->insertItem(" ");
	m_popup->setFont(f);
	f.setPixelSize(ZDim::tileFontSize());
	for (int x=0; x<9; x++)
	{
		m_popup->insertItem(QString::number(x+1));
		for (int y=0; y<9; y++)
		{
			QPushButton* but = new CZudokuTile( this );
			but->setFixedSize(ZDim::tileScreenSize(),ZDim::tileScreenSize());
			but->setFlat(true);
#ifdef Q_WS_MACX
			but->setStyle("windows"); // helps with Mac!
#endif
			but->setFont( f );
			m_boardLayout->addWidget( but, y+(y/3), x+(x/3) );
			m_bg->insert(but,x+9*y);
			connect( but, SIGNAL( pressed(CZudokuTile*, QChar) ), this, SLOT( onKey(CZudokuTile*, QChar) ) );
			connect( but, SIGNAL( pressedMove(int) ), this, SLOT( onKeyMove(int) ) );
		}
	}
	connect( m_bg, SIGNAL( clicked(int) ), this, SLOT( onClick(int) ) );
	QLabel* gap = new QLabel(this);
	QLabel* gap2 = new QLabel(this);
	gap->setFixedSize(2,2);
	gap->setBackgroundColor(black);
	gap2->setFixedSize(2,2);
	gap2->setBackgroundColor(black);
	m_boardLayout->addWidget(gap,3,3);
	m_boardLayout->addWidget(gap2,7,7);
}

CZudokuBoard::~CZudokuBoard()
{
}

void CZudokuBoard::drawSquare(int x, int y, const QString& aText, QColor aColor, QFont aFont)
{
	int butId = x+9*y;
	m_bg->find(butId)->setText(aText);
	m_bg->find(butId)->setFont(aFont);
	setButtonColor(butId,aColor);
}

QChar CZudokuBoard::popup(int x, int y)
{
	int id = x+9*y;
	QButton* pressed = m_bg->find(id);
	QPoint popupPoint = mapToGlobal(pressed->pos());
	popupPoint.setX(popupPoint.x()+ZDim::tileScreenSize()); // don't obscure the column you're editing
	int result = m_popup->exec(popupPoint);
	if (result != -1)
	{
		QChar c = m_popup->text(result)[0];
		if (c==' ')
			c='0';
		return c;
	}
	else
		return 'x';
}
void CZudokuBoard::onClick(int id)
{
	int y = id / 9;
	int x = id % 9;
	emit onClick(x,y);
}
void CZudokuBoard::onKey(CZudokuTile* aTile, QChar aKey)
{
	int id = m_bg->id(aTile);
	int y = id / 9;
	int x = id % 9;
	if (aKey==' ')
		aKey='0'; 
	emit onKey(aKey,x,y);
}
void CZudokuBoard::onKeyMove(int aKey)
{
	m_bg->moveFocus(aKey); 
}
void CZudokuBoard::setButtonColor(int butId, QColor aColor)
{
	QPalette p(m_bg->find(butId)->palette());
	p.setColor(QColorGroup::Button,white);
	p.setColor(QColorGroup::ButtonText,aColor);
	m_bg->find(butId)->setPalette(p);
}

// ---------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------
// The main window

CMainWindow::CMainWindow( QWidget* parent )
    : QMainWindow( parent, "Zudoku" )
{
	setCaption("Zudoku by Figlabs");
	setIcon(QPixmap(iconFile));
	m_stack = new QWidgetStack(this);
	setCentralWidget(m_stack);
		
	m_wholeFrame = new QFrame(m_stack);
	
#ifndef QTOPIA_1_5
	m_helpWin = new QVBox(m_stack);
	m_closeHelp = new QPushButton("Close Help",m_helpWin);
	connect( m_closeHelp, SIGNAL( clicked() ), this, SLOT( onCloseHelp() ) );
	m_helpBrowser = new QTextBrowser(m_helpWin);
	m_helpBrowser->setText(slurp(helpFile));

	m_adverts.setAutoDelete(true);
	int ad=1;
	while (QFile::exists(advertStem+QString::number(ad)+".png"))
	{
		QPixmap* pm=new QPixmap(advertStem+QString::number(ad)+".png");
		m_adverts.append(pm);
		ad++;
	}
	if (ad!=1)
	{
		m_currentAdvert=0;
		m_advertBut= new QPushButton(m_wholeFrame);
		m_advertBut->setFlat(true);
		m_advertBut->setFixedSize(m_adverts.at(0)->size());
		m_advertBut->setFocusPolicy(QWidget::NoFocus);
		connect( m_advertBut, SIGNAL( clicked() ), this, SLOT( onAdvert() ) );
		showNextAdvert();
		m_advertTimer = startTimer(15000); // change every 15 seconds
	}
	else
	{
		m_advertBut= new QPushButton(m_wholeFrame);
		m_advertBut->setText("Go to Fig Labs web site");
		connect( m_advertBut, SIGNAL( clicked() ), this, SLOT( onAdvert() ) );
	}
#endif

	QFont f(tileFontName, 12, QFont::Normal);
	f.setStyleHint(QFont::SansSerif);
	f.setPixelSize(ZDim::labelFontSize());
	m_info = new QLabel("Rating\n---",m_wholeFrame);
	m_info->setFont(f);
	m_info->setFixedWidth(QFontMetrics(f).width("Many Solutions-"));
	m_info->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding));
	
	m_board = new CZudokuBoard(m_wholeFrame);
	connect( m_board, SIGNAL( onKey(QChar,int,int) ), this, SLOT( onKey(QChar,int,int) ) );
	connect( m_board, SIGNAL( onClick(int,int) ), this, SLOT( onClick(int,int) ) );

	m_wholeLayout = new QGridLayout(m_wholeFrame);
#ifndef QTOPIA_1_5
	m_wholeLayout->setResizeMode(QLayout::Fixed);
	m_wholeLayout->addMultiCellWidget(m_advertBut,0,0,0,2,AlignCenter);
	m_wholeLayout->addWidget(m_board,1,1,AlignCenter);
	m_wholeLayout->addWidget(m_info,1,2,AlignCenter);
#else
	// Adapt for swivel screen on Zaurus
	m_sp1=new QSpacerItem(50,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_wholeLayout->addItem(m_sp1,0,0);
	m_sp2=new QSpacerItem(50,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_info->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
	if (width() > height())
	{
		m_wholeLayout->addWidget(m_board,0,1,AlignCenter);
		m_wholeLayout->addWidget(m_info,0,2,AlignCenter);
		m_wholeLayout->addItem(m_sp2,0,3);
	}
	else
	{
		m_wholeLayout->addWidget(m_board,0,1,AlignCenter);
		m_wholeLayout->addWidget(m_info,1,1,AlignCenter);
		m_wholeLayout->addItem(m_sp2,0,2);
	}
#endif

#ifndef QTOPIA_1_5
 	m_menuBar = new QMenuBar(this);
#else
	m_menuBar = new QPEMenuBar(this);
#endif
	m_rating = new QPopupMenu( this );
    m_trivItem = m_rating->insertItem( "Trivial",  this, SLOT(onRating(int)) );
    m_easyItem = m_rating->insertItem( "Easy",  this, SLOT(onRating(int)) );
    m_mediItem = m_rating->insertItem( "Medium",  this, SLOT(onRating(int)) );
    m_diffItem = m_rating->insertItem( "Difficult",  this, SLOT(onRating(int)) );
    m_fienItem = m_rating->insertItem( "Fiendish",  this, SLOT(onRating(int)) );
    m_unlmItem = m_rating->insertItem( "Unlimited",  this, SLOT(onRating(int)) );
	m_rating->setItemParameter(m_trivItem,ETrivial);
	m_rating->setItemParameter(m_easyItem,EEasy);
	m_rating->setItemParameter(m_mediItem,EMedium);
	m_rating->setItemParameter(m_diffItem,EDifficult);
	m_rating->setItemParameter(m_fienItem,EFiendish);
	m_rating->setItemParameter(m_unlmItem,ENoSolution);

	m_file = new QPopupMenu( this );
#ifndef QTOPIA_1_5
	m_file->insertItem( "&Print",  this, SLOT(onPrint()), CTRL+Key_P );
    m_file->insertSeparator();
#endif
	m_file->insertItem( "E&xit",  this, SLOT(onExit()), CTRL+Key_Q );

	m_game = new QPopupMenu( this );
    m_game->insertItem( "S&tart again",  this, SLOT(onPlay()), CTRL+Key_T );
    m_possItem = m_game->insertItem( "Show p&ossible moves", this, SLOT(onTogglePossibles()), CTRL+Key_O );
    m_pencilItem = m_game->insertItem( "&Make pencil marks", this, SLOT(onTogglePencilMarks()), CTRL+Key_M );
    m_solveItem = m_game->insertItem( "Sol&ve", this, SLOT(onSolve()), CTRL+Key_V );
    m_game->insertSeparator();
    m_generateItem = m_game->insertItem( "&New puzzle", this, SLOT(onGenerate()), CTRL+Key_N );
    m_game->insertItem( "New puzzle level", m_rating);
    m_designItem = m_game->insertItem( "&Design mode", this, SLOT(onSetBoard()), CTRL+Key_D );
    m_game->insertItem( "New &blank puzzle", this, SLOT(onClear()), CTRL+Key_B );

	m_menuBar->insertItem( "&File", m_file );
	m_menuBar->insertItem( "&Game", m_game );
	// Qtopia has it's own help system, so we don't need this
#ifndef QTOPIA_1_5
	m_help = new QPopupMenu( this );
	m_help->insertItem( "&Help",  this, SLOT(onHelp()), CTRL+Key_H );
	m_menuBar->insertItem( "&Help", m_help );
#endif

	m_engine = new CZudokuEngine();
	m_settingBoard = false;
	m_showPossibles = false;
	m_pencilMode = false;
	m_solving = false;
	m_generating = false;
	m_game->setItemChecked(m_designItem,m_settingBoard);
	m_game->setItemChecked(m_possItem,m_showPossibles);
	displayBoard();
	m_stack->raiseWidget(m_wholeFrame);

#ifndef QTOPIA_1_5
	if (m_stack->layout())
		m_stack->layout()->setResizeMode(QLayout::Fixed);
	if (layout())
		layout()->setResizeMode(QLayout::Fixed);
#endif	
	m_desiredRating=EMedium;
	updateRatingChecks();
	
	// if we've run before, load the previous state, otherwise generate a new puzzle
	if (QFile::exists(saveFile))
		doOpen(saveFile);
	else
		doGenerate();
	showDifficulty();
}

CMainWindow::~CMainWindow()
{
	killTimers();
	delete m_engine;
}

// -----------------------------------------------------------------------------
// Overrides

void CMainWindow::timerEvent(QTimerEvent*e)
{
	if (e->timerId()==m_workTimer)
	{
		if (m_solving)
		{
			if (!m_engine->solveStep())
			{
				killTimer(m_workTimer);
				m_solving = false;
				m_game->setItemChecked(m_solveItem,m_solving);
				showDifficulty();
			}
		}
		else if (m_generating)
		{
			ZudokuLevel current;
			if (!m_engine->generateStep(m_desiredRating,current))
			{
				killTimer(m_workTimer);
				m_generating = false;
				m_game->setItemChecked(m_generateItem,m_generating);
				showDifficulty();
			}
			else
			{
				showWorkingDifficulty(current);
			}
		}
		displayBoard();
	}
	else
	{
		showNextAdvert();
	}
}

void CMainWindow::resizeEvent(QResizeEvent*e)
{
	// if we're on a zaurus, check to see if we've gone to portrait or landscape and lay out accordingly
#ifndef QTOPIA_1_5
	QMainWindow::resizeEvent(e);
#else
	// Adapt for swivel screen on Zaurus
	delete m_wholeLayout;
	m_wholeLayout = new QGridLayout(m_wholeFrame);
	m_sp1=new QSpacerItem(50,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_sp2=new QSpacerItem(50,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_wholeLayout->addItem(m_sp1,0,0);
	m_wholeLayout->addWidget(m_board,0,1,AlignCenter);
	m_wholeLayout->addItem(m_sp2,0,3);
	if (e->size().width() > e->size().height())
	{
		m_wholeLayout->addWidget(m_info,0,2,AlignCenter);
	}
	else
	{
		m_wholeLayout->addWidget(m_info,1,1,AlignCenter);
	}
	QMainWindow::resizeEvent(e);
	hide();
	show();
#endif
}

#ifndef QTOPIA_1_5
void CMainWindow::closeEvent ( QCloseEvent * e )
{
	e->accept();
	onExit();
}
#endif

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// Slots - menu options, clicks, key presses

void CMainWindow::onClick(int x, int y)
{
	if (m_settingBoard || m_engine->state(x,y)!=EFilledOrigOk)
	{
		QChar c = m_board->popup(x,y);
		if (c!='x')
			doMove(c,x,y);
	}
}

void CMainWindow::onKey(QChar aKey, int x, int y)
{
	doMove(aKey,x,y);
}

void CMainWindow::onRating(int aRating)
{
	ZudokuLevel level = (ZudokuLevel)aRating;
	m_desiredRating = level;
	updateRatingChecks();
}

void CMainWindow::onGenerate()
{
	if (okToProceed("Replace the current puzzle?"))
	{
		doGenerate();
	}
}
void CMainWindow::doGenerate()
{
	if (!m_generating)
	{
		m_settingBoard = false;
		m_engine->generateStart();
		m_info->setText("Working!\n ");
		m_workTimer = startTimer(workTime);
	}
	else
	{
		killTimer(m_workTimer);
		showDifficulty();
	}
	m_generating = !m_generating;
	m_game->setItemChecked(m_generateItem,m_generating);
	displayBoard();
}

void CMainWindow::onSolve()
{
	if (okToProceed("Let Zudoku solve it for you?"))
	{
		if (!m_solving)
		{
			m_settingBoard = false;
			m_game->setItemChecked(m_designItem,m_settingBoard);
			m_info->setText("Solving!\n ");
			m_engine->backToStart();
			if (m_engine->solveStart(true))
			{
				displayBoard();
				m_workTimer = startTimer(workTime);
			}
		}
		else
		{
			killTimer(m_workTimer);
			m_engine->backToStart();
			showDifficulty();
			displayBoard();
		}
		m_solving = !m_solving;
		m_game->setItemChecked(m_solveItem,m_solving);
	}
}

void CMainWindow::onTogglePossibles()
{
	m_showPossibles = !m_showPossibles;
	displayBoard();
	m_game->setItemChecked(m_possItem,m_showPossibles);
}

void CMainWindow::onTogglePencilMarks()
{
	m_pencilMode = !m_pencilMode;
	displayBoard();
	m_game->setItemChecked(m_pencilItem,m_pencilMode);
}

void CMainWindow::onClear()
{
	if (okToProceed("Clear the current puzzle?"))
	{
		m_engine->setBoard(blankBoard);
		displayBoard();
	}
}

void CMainWindow::onSetBoard()
{
	if (m_settingBoard)
		showDifficulty();
	else
		m_info->setText("Design\nmode");
	m_settingBoard = !m_settingBoard;
	m_game->setItemChecked(m_designItem,m_settingBoard);
	m_engine->backToStart();
	displayBoard();
}

void CMainWindow::onPlay()
{
	if (m_settingBoard)
		showDifficulty();
	m_settingBoard = false;
	m_game->setItemChecked(m_designItem,m_settingBoard);
	m_engine->backToStart();
	displayBoard();
}

void CMainWindow::onPrint()
{
#ifndef QT_NO_PRINTER
	QPrinter* printer = new QPrinter();
    if ( printer->setup( this ) )
	{
        QPainter p;
        if ( !p.begin( printer ) )
            return;
        // draw the board
        QPaintDeviceMetrics metrics( p.device() );
        int dpiy = metrics.logicalDpiY();
        int margin = (int) ( (2/2.54)*dpiy ); // 2 cm margins
        QRect view( margin, margin, metrics.width() - 2*margin, metrics.height() - 2*margin );
		
		// puzzle size should be 12cm x 12cm
		// work out 12cm in drawing units (we assume aspect ratio of 1:1)
		double printPuzzleSize = (12.0/2.54)*(double)dpiy;
		// size of the thicker lines on the board
		double boost = 5;
		// size of the puzzle normally
		double nonScalePuzzleSize = ZDim::tilePrintSize()*9 + boost*2;
		// scaling factor
		m_printScaleFactor = printPuzzleSize / nonScalePuzzleSize;
		
		boost = boost * m_printScaleFactor;
		int tileScaledPrintSize = (int)(ZDim::tilePrintSize() * m_printScaleFactor);

		// scale the advert
		QPixmap printAd(*(m_adverts.at(0)));
		int adH = printAd.height();
		int adW = printAd.width();
		QImage adIm = printAd.convertToImage();
		printAd.convertFromImage(adIm.smoothScale((int)(adW*m_printScaleFactor),(int)(adH*m_printScaleFactor)));
		
		p.drawPixmap((metrics.width() - printAd.width())/2,margin,printAd);
		int xOrig = int((metrics.width() - printPuzzleSize)/2);
		int yOrig = int(margin*2 + printAd.height());
		QPen thin(black,0);
		QPen thick(black,(int)boost);
		p.setPen(thick);
		p.drawRect(xOrig,yOrig,(int)(tileScaledPrintSize*9 + boost*2),(int)(tileScaledPrintSize*9 + boost*2));
		p.drawRect(xOrig+int(3*tileScaledPrintSize+boost/2),yOrig,(int)(tileScaledPrintSize*3+boost),(int)(tileScaledPrintSize*9 + boost*2));
		p.drawRect(xOrig,yOrig+(int)(3*tileScaledPrintSize+boost/2),(int)(tileScaledPrintSize*9 + boost*2),(int)(tileScaledPrintSize*3+boost));
		p.setPen(thin);
		for (int x=0; x<9; x++)
		{
			for (int y=0; y<9; y++)
			{
				int xboost = (x/3)*(int)boost;
				int yboost = (y/3)*(int)boost;
				displaySquare(x,y,&p,(int)(x*tileScaledPrintSize + xOrig + xboost),(int)(y*tileScaledPrintSize +yOrig+yboost));
			}
		}
    }
	delete printer;
#endif	
}

void CMainWindow::onHelp()
{
	m_stack->raiseWidget(m_helpWin);
	m_menuBar->hide();
}
void CMainWindow::onCloseHelp()
{
	m_stack->raiseWidget(m_wholeFrame);
	m_menuBar->show();
}

void CMainWindow::onAdvert()
{
	OpenLink::open(this,advertUrl);
}

void CMainWindow::onExit()
{
	doSave(saveFile);
#ifndef QTOPIA_1_5
	qApp->quit();
#else
	close();
#endif
}

// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

bool CMainWindow::okToProceed(const QString& warning)
{
	// ask the warning, and get user confirmation it is ok to proceed
	int result=QMessageBox::warning(this,"Are you sure?",warning,"OK","Cancel",QString::null,1,1);
	return result==0;
}

void CMainWindow::showNextAdvert()
{
#ifndef QTOPIA_1_5
	m_advertBut->setPixmap(*(m_adverts.at(m_currentAdvert)));
	m_currentAdvert++;
	if (m_currentAdvert==m_adverts.count())
		m_currentAdvert=0;
#endif
}

void CMainWindow::displayBoard()
{
	if (m_settingBoard)
		m_board->setBoardColor(red);
	else
		m_board->setBoardColor(black);
		
	for (int x=0; x<9; x++)
	{
		for (int y=0; y<9; y++)
		{
			displaySquare(x,y);
		}
	}
}

void CMainWindow::displaySquare(int x, int y, QPainter* printer, int px, int py)
{
	double scale=1.0;
	if (printer)
		scale = m_printScaleFactor;
	
	QString squareConts;
	QFont f(tileFontName, 12, QFont::Normal);
	f.setStyleHint(QFont::SansSerif);
	f.setPixelSize((int)(scale*ZDim::tileFontSize()));
	QColor col = black;
	
	ZudokuSquareState state = m_engine->state(x,y);
	if (m_settingBoard)
		squareConts = m_engine->startSquare(x,y);
	else
		squareConts = m_engine->square(x,y);
	if (squareConts=="0")
		squareConts=" ";
	else if (m_generating)
		squareConts="?";
	if (squareConts==" ")
	{
		if (m_showPossibles)
		{
			QString poss = m_engine->possibles(x,y);
			f.setPixelSize((int)(scale*ZDim::tileFontSmall()));
			col = darkGreen;
			poss = doFormatSmallNumbers(poss);
			if (poss.length()>7 || (!ZDim::hiRes() && poss.length()>3))
			{
				f.setPixelSize((int)(scale*ZDim::tileFontSize()));
			}
			else if (poss=="")
			{
				poss="!";
				col = red;
				f.setPixelSize((int)(scale*ZDim::tileFontSize()));
				f.setBold(true);
			}
			squareConts=poss;
		}
		else
		{
			// see if there are any pencil marks to display
			QString pencilMarks = m_engine->getPencil(x,y);
			f.setPixelSize((int)(scale*ZDim::tileFontSmall()));
			col = darkYellow;
			squareConts = doFormatSmallNumbers(pencilMarks);
		}
	}
	
	if (state==EFilledOrigOk)
	{
		f.setBold(true);
		col = black;
	}
	else if (state==EFilledUserOk)
	{
		f.setItalic(true);
		col = darkGray;
	}
	else if (state==EFilledUserWrong)
	{
		f.setItalic(true);
		col = red;
	}
	else if (state==EFilledOrigWrong)
	{
		col = darkRed;
		f.setBold(true);
	}
	if (!printer)
		m_board->drawSquare(x,y,squareConts,col,f);
	else
	{
		// display the square on a printer
		printer->drawRect(px,py,(int)(m_printScaleFactor*ZDim::tilePrintSize()),(int)(m_printScaleFactor*ZDim::tilePrintSize()));
		printer->setFont(f);
		printer->drawText(px,py,(int)(m_printScaleFactor*ZDim::tilePrintSize()),(int)(m_printScaleFactor*ZDim::tilePrintSize()),Qt::AlignCenter,squareConts);
	}
}

QString CMainWindow::doFormatSmallNumbers(QString poss)
{
	QString result;
	if (poss.length()>7 || (!ZDim::hiRes() && poss.length()>3))
	{
		poss = "*";
	}
	else if (poss.length()>5)
	{
		poss.insert(3,"\n");
	}
	else if (poss.length()>3)
	{
		poss.insert(2,"\n");
	}
	else if (poss.length()==2)
	{
		poss.insert(1," ");
	}
	return poss;
}

void CMainWindow::doMove(QChar aP, int x, int y)
{
	if (m_settingBoard)
	{
		if (m_engine->valid(aP,x,y))
		{
			m_engine->setStartSquare(aP,x,y);
		}
		else
		{
			// perhaps give feedback
		}
	}
	else
	{
		if (m_pencilMode)
			m_engine->togglePencil(aP,x,y);
		else
			m_engine->move(aP,x,y);
	}
	displayBoard();
}

void CMainWindow::showDifficulty()
{
	ZudokuLevel level = m_engine->difficulty();
	m_info->setText("Rating:\n"+ratingFromLevel(level));
}
void CMainWindow::showWorkingDifficulty(ZudokuLevel level)
{
	m_info->setText("Working!\n"+ratingFromLevel(level));
}
void CMainWindow::showFinalDifficulty(ZudokuLevel level)
{
	m_info->setText("Rating:\n"+ratingFromLevel(level));
}
QString CMainWindow::ratingFromLevel(ZudokuLevel level)
{
	QString rating;
	if (level == ENoSolution)
		rating = "No solution";
	else if (level == EManySolutions)
		rating = "Many solutions";
	else if (level == ETooEasy)
		rating = "Too Easy!";
	else if (level == ETrivial)
		rating = "Trivial";
	else if (level == EEasy)
		rating = "Easy";
	else if (level == EMedium)
		rating = "Medium";
	else if (level == EDifficult)
		rating = "Difficult";
	else if (level == EFiendish)
		rating = "Fiendish";
	return rating;
}

void CMainWindow::updateRatingChecks()
{
	m_rating->setItemChecked(m_trivItem,false);
	m_rating->setItemChecked(m_easyItem,false);
	m_rating->setItemChecked(m_mediItem,false);
	m_rating->setItemChecked(m_diffItem,false);
	m_rating->setItemChecked(m_fienItem,false);
	m_rating->setItemChecked(m_unlmItem,false);
	switch (m_desiredRating)
	{
	case ETrivial:
		m_rating->setItemChecked(m_trivItem,true);
		break;
	case EEasy:
		m_rating->setItemChecked(m_easyItem,true);
		break;
	case EMedium:
		m_rating->setItemChecked(m_mediItem,true);
		break;
	case EDifficult:
		m_rating->setItemChecked(m_diffItem,true);
		break;
	case EFiendish:
		m_rating->setItemChecked(m_fienItem,true);
		break;
	default:
		m_rating->setItemChecked(m_unlmItem,true);
		break;
	}
}

void CMainWindow::doOpen(const QString& aFile)
{
	m_engine->setBoard(slurp(aFile));
	displayBoard();
}
void CMainWindow::doSave(const QString& aFile)
{
    QFile file( aFile );
	QString encBoard = m_engine->getBoard(false);
    if ( file.open( IO_WriteOnly ) )
	{
		file.writeBlock(QCString(encBoard));
        file.close();
	}
	displayBoard();
}
QString CMainWindow::slurp(const QString& aFile)
{
    QFile file( aFile );
	QString slurp;
    if ( file.open( IO_ReadOnly ) )
	{
		QTextStream stream( &file );
        while ( !stream.atEnd() ) {
            slurp += stream.readLine() + "\n";
        }
        file.close();
	}
	return slurp;
}

#ifdef Q_WS_MACX
QString getMacBundlePath()
{
	CFURLRef pluginRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(pluginRef, 
                                               kCFURLPOSIXPathStyle);
    const char *pathPtr = CFStringGetCStringPtr(macPath, 
                                               CFStringGetSystemEncoding());
    QString path(pathPtr);
    CFRelease(pluginRef);
    CFRelease(macPath);
	return path;
}
#endif

#include <qcursor.h>
#ifdef Q_WS_WIN
#include <windows.h>
#endif

const bool OpenLink::open(QWidget *widget, const QString &filename)
{
    bool retval = false;
#ifndef QTOPIA_1_5
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#ifdef Q_WS_X11
    Q_UNUSED(widget);
    // Assume we have KDE
    QString s("kfmclient exec \"");
    s += filename;
    s += "\"";
    retval = (system(s.ascii()) == 0);
#endif

#ifdef Q_WS_MACX
    // Running on a Mac in OS X
    Q_UNUSED(widget);
    QString s("open \"");
    s += filename;
    s += "\"";
    retval = (system(s.ascii()) == 0);
#endif

#ifdef Q_WS_WIN
    // Running in an MS Windows environment
    if (NULL != widget) {
        retval = (reinterpret_cast<int>(ShellExecuteA(widget->winId(), "open",
					filename.ascii(),NULL, NULL, SW_SHOW)) > 32);
    }
#endif

    QApplication::restoreOverrideCursor();
#endif
    return retval;
}
