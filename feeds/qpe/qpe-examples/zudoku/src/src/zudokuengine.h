#ifndef zudokuengine_h
#define zudokuengine_h

#include <qstring.h>
#include <qstringlist.h>
#include <qtextstream.h>

#ifndef QTOPIA_1_5
#include <qptrlist.h>
#else
#include <qlist.h>
typedef QCollection QPtrCollection;
#endif


#include <stdlib.h>

typedef enum ZudokuLevel { ENoSolution, EManySolutions, ETooEasy, ETrivial, EEasy, EMedium, EDifficult, EFiendish } ZudokuLevel;
typedef enum ZudokuSquareState { EEmpty, EFilledOrigOk, EFilledOrigWrong, EFilledUserOk, EFilledUserWrong } ZudokuSquareState;

const QString startLabel = "Start:";
const QString currentLabel = "Current:";

const QString blankBoard = "Start:\n000000000\n000000000\n000000000\n000000000\n000000000\n000000000\n000000000\n000000000\n000000000\n";
const QString pieces="123456789";

// if we go beyond this I reckon we're stuck
const int stepsUpperBound = 600;

class CZudoPossiblesEntry
{
public:
	CZudoPossiblesEntry(int aX, int aY, QString aPossibles) : m_x(aX), m_y(aY), m_currentPossible(0), m_possibles(aPossibles) {}

	QChar nextPossible()
	{
		if (m_currentPossible<m_possibles.length())
		{
			m_currentPossible++;
			return m_possibles[m_currentPossible-1];
		}
		else
		{
			return '0';
		}
	}
	void setPossibles(const QString& aPossibles) { m_possibles = aPossibles; }
	QString possibles() { return m_possibles; }
	int x() { return m_x; }
	int y() { return m_y; }
	
private:
	int m_x;
	int m_y;
	unsigned m_currentPossible;
	QString m_possibles;
};

// list of possibles, sortable by number of possibles
class CPossiblesList: public
#ifndef QTOPIA_1_5
	QPtrList<CZudoPossiblesEntry>
#else
	QList<CZudoPossiblesEntry>
#endif
{
public:
	CPossiblesList():
#ifndef QTOPIA_1_5
		QPtrList<CZudoPossiblesEntry>() {}
#else
		QList<CZudoPossiblesEntry>() {}
#endif
	virtual ~CPossiblesList() {}

	virtual int compareItems(QPtrCollection::Item item1, QPtrCollection::Item item2)
	{
		CZudoPossiblesEntry* e1 = static_cast<CZudoPossiblesEntry *>(item1);
		CZudoPossiblesEntry* e2 = static_cast<CZudoPossiblesEntry *>(item2);
		const unsigned int l1 = e1->possibles().length();
		const unsigned int l2 = e2->possibles().length();
		if(l1 < l2)
			return -1;
		else if(l1 > l2)
			return 1;
		else /* They're equal */
			return 0;
	}
};
	
class CZudokuEngine
{
public:
	CZudokuEngine();
	CZudokuEngine(const QString& aBoard);
	~CZudokuEngine();

	//
	ZudokuLevel difficulty();

	// set the board up from stored representation
	void setBoard(const QString& aBoard);
	QString getBoard(bool aJustStart=false);

	// reset the playing board back to the start
	void backToStart();
	
	// place one piece, given the current board setup
	bool solveStart(bool findOnlyOne=false, bool aScramble=false);
	bool solveStep(bool aScramble=false);

	// generate - make a new puzzle
	void generateStart();
	bool generateStep(ZudokuLevel req, ZudokuLevel& act);

	// hint - return the details of next valid move
	bool hint(QChar& p, int& x, int&y);

	// did we finish it?
	bool solved();

	// find the number of possible solutions, given starting board state
	int solutions();
	
	// add/remove a pencil mark
	void togglePencil(QChar val,int x, int y);
	// read pencil marks
	QString getPencil(int x, int y);

	ZudokuSquareState state(int x, int y);

	bool move(QChar val,int x, int y);
	QChar square(int x, int y);

	void setStartSquare(QChar val,int x, int y);
	QChar startSquare(int x, int y);

	bool valid(QChar val,int x, int y);
	bool boardValid();

	QString possibles(int x, int y, bool aScramble=false);
	
private:
	void fillPossiblesList(CPossiblesList& aList, bool aScramble=false);
	void refillPossiblesList(bool aScramble=false);
	void dumpPossiblesList();
	bool tryMove();
	void backtrack();
	bool tileHasToBeAt(QChar val,int x, int y);
	QString scramble(const QString& aInput);
	void generateFilledBoard();
	ZudokuLevel levelFromSteps(int aSteps);
	CZudoPossiblesEntry* pencilMarksAt(int x, int y);

	QStringList m_currentBoard;
	QStringList m_startBoard;
	bool m_findOnlyOne;
	CPossiblesList m_possibles;
	unsigned m_currentPossiblePointer;
	int m_solutions;
	int m_steps;
	CPossiblesList m_notTried;
	CPossiblesList m_pencilMarks;
};

#endif
