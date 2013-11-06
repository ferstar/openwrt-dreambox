#include <qpushbutton.h>
#include <qtopia/qpeapplication.h>
#include <qfont.h>

int main(int argc, char **argv)
{
	// test the argv[] from the hello.desktop,
	// as the Exec=hello -test.
	// proved the *.desktop could pass the argv[] !
	qWarning("TEST: argv[0]=%s",argv[0]);
	qWarning("TEST: argv[1]=%s",argv[1]);

	QPEApplication a( argc, argv );
	QPushButton hellobtn("Hello World !", 0);
	hellobtn.resize(240,320);
	hellobtn.setCaption("Qt Example - Hello World");
	hellobtn.setFont( QFont( "Times", 18, QFont::Bold ) );
	QObject::connect( &hellobtn, SIGNAL(clicked()), &a, SLOT(quit()) );
	a.showMainWidget(&hellobtn);
	return a.exec();
}
