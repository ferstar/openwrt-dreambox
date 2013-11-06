#include <QtGui/QApplication>
#include "mapwidget.h"
#include <QTextCodec>
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef Q_OS_WIN32
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
#else
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB18030"));
#endif

    MapWidget map;
    map.show();
    return a.exec();
}
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
