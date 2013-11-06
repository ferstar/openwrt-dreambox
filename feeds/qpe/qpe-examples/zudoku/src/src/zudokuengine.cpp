
#include "zudokuengine.h"


CZudokuEngine::CZudokuEngine()
{
	setBoard(blankBoard);
	backToStart();
	m_possibles.setAutoDelete(true);
	m_pencilMarks.setAutoDelete(true);
}
CZudokuEngine::CZudokuEngine(const QString& aBoard)
{
	setBoard(aBoard);
	backToStart();
}
CZudokuEngine::~CZudokuEngine()
{
}

// -------------------------------------------------------------------------------------
// generating

void CZudokuEngine::generateStart()
{
	generateFilledBoard();
	m_notTried.clear();
	int x,y;
	for (y=0; y<9; y++)
	{
		for (x=0; x<9; x++)
		{
			CZudoPossiblesEntry* e= new CZudoPossiblesEntry(x,y,"");
			m_notTried.append(e);
		}
	}
}
bool CZudokuEngine::generateStep(ZudokuLevel req, ZudokuLevel& act)
{
	int x,y;
	if (m_notTried.count()>0)
	{
		// pick one at random to remove
		int remove = (int) (((double)m_notTried.count() )*rand()/(RAND_MAX+1.0));
		QChar val;
		x = m_notTried.at(remove)->x();
		y = m_notTried.at(remove)->y();
		m_notTried.remove(remove);
		val = startSquare(x,y);
		setStartSquare('0',x,y);
		if (solutions()!=1)
		{
			// the last tile we took away caused the puzzle to have >1 solution
			// so put it back
			setStartSquare(val,x,y);	
			act = EManySolutions;
		}
		else
			act = levelFromSteps(m_steps);
		if (act==req)
			return false;
		return true;
	}
	else
		return false;
}
void CZudokuEngine::generateFilledBoard()
{
	// clear up
	setBoard(blankBoard);
	backToStart();
	
	// Just do a solve on a blank board, but picking random digits
	if (solveStart(true,true))
	{
		while (solveStep(true))
			;
	}
	
	// Move the current position to the board state
	for (int y=0; y<9; y++)
	{
		m_startBoard[y]=m_currentBoard[y];
	}
}

ZudokuLevel CZudokuEngine::difficulty()
{
	ZudokuLevel level;
	int solns = solutions();
	if (solns==0)
		level = ENoSolution;
	else if (solns>1)
		level = EManySolutions;
	else
	{
		level=levelFromSteps(m_steps);
	}
	return level;
}

ZudokuLevel CZudokuEngine::levelFromSteps(int aSteps)
{
	ZudokuLevel level;
	if (aSteps<20)
		level = ETooEasy;
	else if (aSteps<30)
		level = ETrivial;
	else if (aSteps<40)
		level = EEasy;
	else if (aSteps<55)
		level = EMedium;
	else if (aSteps<110)
		level = EDifficult;
	else
		level = EFiendish;
	return level;
}

// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// solving

bool CZudokuEngine::solveStart(bool findOnlyOne,bool aScramble)
{
	m_findOnlyOne = findOnlyOne;
	backToStart();
	if (boardValid())
	{
		m_possibles.clear();
		fillPossiblesList(m_possibles,aScramble);
		//dumpPossiblesList();
		m_solutions = 0;
		m_steps = 0;
		if (m_possibles.count() > 0)
		{
			m_currentPossiblePointer = 0;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
bool CZudokuEngine::tryMove()
{
	// go to the current possibles entry, pick the next piece and place it
	CZudoPossiblesEntry* e= m_possibles.at(m_currentPossiblePointer);
	QChar p = e->nextPossible();
	if (p != '0')
	{
		move(p,e->x(),e->y());
		return true;
	}
	else
		return false;
}
void CZudokuEngine::backtrack()
{
	m_currentPossiblePointer--;
	CZudoPossiblesEntry* e= m_possibles.at(m_currentPossiblePointer);
	move('0',e->x(),e->y());
}
bool CZudokuEngine::solveStep(bool aScramble)
{
	// try and make the next sensible move
	bool impossible = false;
	m_steps++;
	if (m_steps>stepsUpperBound)
		return false;
	while (!tryMove())
	{
		// move failed
		// if there are no moves left to backtrack, the puzzle is impossible to solve!
		if (m_currentPossiblePointer==0)
		{
			impossible = true;
			break;
		}
		backtrack();
	}	
	if (!impossible)
	{
		// advance to next entry
		m_currentPossiblePointer++;
		if (m_currentPossiblePointer>=m_possibles.count())
		{
			m_solutions++;
			if (m_solutions>1 || m_findOnlyOne)
			{
				return false;
			}
			// we found a solution - see if there are any more
			backtrack();
		}
		else
			// regenerate the rest of the possibles list
			refillPossiblesList(aScramble);
		return true;
	}
	else
	{
		// We've done finding solutions, or there are none
		return false;
	}
}
bool CZudokuEngine::solved()
{
	for (int y=0; y<9; y++)
	{
		for (int x=0; x<9; x++)
		{
			ZudokuSquareState s = state(x,y);
			if (s==EEmpty || s==EFilledUserWrong  )
				return false;
		}
	}
	return true;
}
int CZudokuEngine::solutions()
{
	QString saveBoard=getBoard(false);
	if (solveStart())
	{
		while (solveStep())
			;
	}
	setBoard(saveBoard);
	return m_solutions;
}

// find every empty square, add the list of possibles for that square, sort by length of possibles list
void CZudokuEngine::fillPossiblesList(CPossiblesList& aList,bool aScramble)
{
	for (int y=0; y<9; y++)
	{
		for (int x=0; x<9; x++)
		{
			if (state(x,y)==EEmpty)
			{
				CZudoPossiblesEntry* e= new CZudoPossiblesEntry(x,y,possibles(x,y,aScramble));
				aList.append(e);
			}
		}
	}
	aList.sort();
}

// starting from the current position in the list, regenerate the list of possibles
// and sort just the new section
void CZudokuEngine::refillPossiblesList(bool aScramble)
{
	// lose the end of the list
	while (m_possibles.count()>m_currentPossiblePointer)
		m_possibles.remove(m_possibles.count()-1);
	// build up a new list
	CPossiblesList newPossibles;
	fillPossiblesList(newPossibles,aScramble);
	// add the new list entries to our master list
#ifndef QTOPIA_1_5
	QPtrListIterator<CZudoPossiblesEntry> it( newPossibles );
#else
	QListIterator<CZudoPossiblesEntry> it( newPossibles );
#endif
	CZudoPossiblesEntry *entry;
	while ( (entry = it.current()) != 0 )
	{
		m_possibles.append(entry);
		++it;
	}
	//dumpPossiblesList();
}

void CZudokuEngine::dumpPossiblesList()
{
#ifndef QTOPIA_1_5
	QPtrListIterator<CZudoPossiblesEntry> it( m_possibles );
#else
	QListIterator<CZudoPossiblesEntry> it( m_possibles );
#endif
	CZudoPossiblesEntry *entry;
	printf("-----------\nPossibles...\n");
	while ( (entry = it.current()) != 0 )
	{
		printf("(%d,%d) - %s\n",entry->x(),entry->y(),entry->possibles().ascii());
		++it;
	}
	printf("-----------\n");
}

// at square (x,y), return a list of all the possible pieces that can go there
QString CZudokuEngine::possibles(int x, int y, bool aScramble)
{
	QString result;
	if (state(x,y)==EEmpty)
	{
		for (int poss=0; poss<9; poss++)
		{
			QChar cur = pieces[poss];
			if (valid(cur,x,y))
			{
				if (tileHasToBeAt(cur,x,y))
				{
					result=cur;
					break;
				}
				result += cur;
			}
		}
	}
	if (aScramble)
		result = scramble(result);
	return result;
}

QString CZudokuEngine::scramble(const QString& aInput)
{
	QString result;
	QString work = aInput;
	while (work.length() > 0)
	{
		int idx = (int) (((double)(work.length()))*rand()/(RAND_MAX+1.0));
		result += work[idx];
		work.remove(idx,1);
	}
	return result;
}

// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// Pencil Marks

// add/remove a pencil mark
void CZudokuEngine::togglePencil(QChar val,int x, int y)
{
	// is there a pencil mark entry for this square?
	CZudoPossiblesEntry *entry=pencilMarksAt(x,y);
	if (entry)
	{
		QString curEntry = entry->possibles();
		if (val=='0')
			entry->setPossibles("");
		else if (curEntry.contains(val))
		{
			int at = curEntry.find(val);
			curEntry.remove(at,1);
			entry->setPossibles( curEntry );
		}
		else
		{
			entry->setPossibles( curEntry.append(val) );
		}
	}
	else if (val != '0')
	{
		CZudoPossiblesEntry* e= new CZudoPossiblesEntry(x,y,QString(val));
		m_pencilMarks.append(e);
	}
}

CZudoPossiblesEntry* CZudokuEngine::pencilMarksAt(int x, int y)
{
	CZudoPossiblesEntry *result=NULL, *entry = NULL;
#ifndef QTOPIA_1_5
	QPtrListIterator<CZudoPossiblesEntry> it( m_pencilMarks );
#else
	QListIterator<CZudoPossiblesEntry> it( m_pencilMarks );
#endif
	while ( (entry = it.current()) != 0 )
	{
		if (entry->x()==x && entry->y()==y)
		{
			result=entry;
			break;
		}
		++it;
	}
	return result;
}

// read pencil marks
QString CZudokuEngine::getPencil(int x, int y)
{
	QString result="";
	CZudoPossiblesEntry *entry=pencilMarksAt(x,y);
	if (entry)
		result = entry->possibles();
	return result;
}



// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------
// basic routines for placing tiles, and testing validity

bool CZudokuEngine::tileHasToBeAt(QChar val,int x, int y)
{
	// does value 'val' _have_ to be in this square - i.e. is is valid anywhere else in either 3x3, row or column

	// 1 - test 3x3 first
	int xgroup = x / 3;
	int ygroup = y / 3;
	int testx, testy;
	bool hasToBeHere = true;
	for (testx=0;testx<3; testx++)
	{
		for (testy=0;testy<3; testy++)
		{
			if (x==(xgroup*3)+testx && y==(ygroup*3)+testy)
				continue;
			if (state((xgroup*3)+testx,(ygroup*3)+testy)==EEmpty && valid(val,(xgroup*3)+testx,(ygroup*3)+testy))
			{
				hasToBeHere = false;
				break;
			}
		}
		if (!hasToBeHere)
			break;
	}
	if (!hasToBeHere)
	{
		// 2 - check the row we are in
		hasToBeHere = true;
		testy = y;
		for (int testx=0;testx<9; testx++)
		{
			if (testx==x)
				continue;
			if (state(testx,testy)==EEmpty && valid(val,testx,testy))
			{
				hasToBeHere = false;
				break;
			}
		}
	}
	if (!hasToBeHere)
	{
		// 3 - check the column we are in
		testx = x;
		for (int testy=0;testy<9; testy++)
		{
			if (testy==y)
				continue;
			if (state(testx,testy)==EEmpty && valid(val,testx,testy))
			{
				hasToBeHere = false;
				break;
			}
		}
	}
	return hasToBeHere;
}

bool CZudokuEngine::boardValid()
{
	for (int y=0; y<9; y++)
	{
		for (int x=0; x<9; x++)
		{
			ZudokuSquareState s = state(x,y);
			if (s==EFilledOrigWrong || s==EFilledUserWrong)
				return false;
		}
	}
	return true;
}

bool CZudokuEngine::valid(QChar val,int x, int y)
{
	// always valid to blank a square
	if (val=='0')
		return true;
	// does putting val at x,y work?
	// 1 - check the group of 9 tiles we are in
	int xgroup = x / 3;
	int ygroup = y / 3;
	int testx, testy;
	for (testx=0;testx<3; testx++)
	{
		for (testy=0;testy<3; testy++)
		{
			if (x==(xgroup*3)+testx && y==(ygroup*3)+testy)
				continue;
			if (square((xgroup*3)+testx,(ygroup*3)+testy)==val)
				return false;
		}
	}
	// 2 - check the row we are in
	testy = y;
	for (testx=0;testx<9; testx++)
	{
		if (testx==x)
			continue;
		if (square(testx,testy)==val)
			return false;
	}
	// 3 - check the column we are in
	testx = x;
	for (testy=0;testy<9; testy++)
	{
		if (testy==y)
			continue;
		if (square(testx,testy)==val)
			return false;
	}
	return true;
}
bool CZudokuEngine::move(QChar val,int x, int y)
{
	if (state(x,y) != EFilledOrigOk && state(x,y) != EFilledOrigWrong)
	{
		m_currentBoard[y][x] = val;
	}
	else
		return false;
	return true;
}
void CZudokuEngine::setStartSquare(QChar val,int x, int y)
{
	m_startBoard[y][x] = val;
	m_currentBoard[y][x] = val;
}
ZudokuSquareState CZudokuEngine::state(int x, int y)
{
	QChar curSquare = square(x,y);
	QChar staSquare = startSquare(x,y);
	
	if (staSquare!='0')
	{
		if (!valid(staSquare,x,y))
			return EFilledOrigWrong;
		return EFilledOrigOk;
	}
	else
	{
		if (curSquare=='0')
			return EEmpty;
		if (!valid(curSquare,x,y))
			return EFilledUserWrong;
		return EFilledUserOk;
	}
}
QChar CZudokuEngine::square(int x, int y)
{
	QString row = m_currentBoard[y];
	return row[x];
}
QChar CZudokuEngine::startSquare(int x, int y)
{
	QString row = m_startBoard[y];
	return row[x];
}
void  CZudokuEngine::backToStart()
{
	m_currentBoard.clear();
	for (int y=0; y<9; y++)
	{
		m_currentBoard << m_startBoard[y];
	}
	m_pencilMarks.clear();
}
// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------
// setup board from stored state

void CZudokuEngine::setBoard(const QString& aBoard)
{
	// import board from stored format
	QString b = aBoard;
	QTextIStream str(&b);
	bool expectStartBoard = false;
	bool expectCurrentBoard = false;
	bool expectLabel = true;
	m_startBoard.clear();
	m_currentBoard.clear();
	while (!str.eof())
	{
		QString line = str.readLine();
		if (expectLabel)
		{
			if (line.compare(startLabel)==0)
			{
				expectStartBoard = true;
				expectLabel = false;
			}
			else if (line.compare(currentLabel)==0)
			{
				expectCurrentBoard = true;
				expectLabel = false;
			}
			else
			{
				// oops, keep trying
			}
		}
		else if (expectStartBoard)
		{
			m_startBoard << line;
			if (m_startBoard.count()==9)
			{
				expectStartBoard = false;
				expectLabel = true;
			}
		}
		else if (expectCurrentBoard)
		{
			m_currentBoard << line;
			if (m_currentBoard.count()==9)
			{
				expectCurrentBoard = false;
				expectLabel = true;
			}
		}
	}
	if (m_currentBoard.count()!=9)
	{
		backToStart();
	}
}
QString CZudokuEngine::getBoard(bool aJustStart)
{
	QString board;
	board = startLabel+"\n";
	for (int y=0; y<9; y++)
	{
		board += m_startBoard[y]+"\n";
	}
	if (!aJustStart)
	{
		board += currentLabel+"\n";
		for (int y=0; y<9; y++)
		{
			board += m_currentBoard[y]+"\n";
		}
	}
	return board;
}
// -------------------------------------------------------------------------------------
