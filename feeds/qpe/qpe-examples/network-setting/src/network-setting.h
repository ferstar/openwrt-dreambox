#ifndef TMAINFORM_H
#define TMAINFORM_H

#include "network-setting-base.h"
#include <qvariant.h>


class TMainForm : public TMainFormBase
{
    Q_OBJECT

public:
    TMainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel);
    ~TMainForm() {}

public slots:
    void closeButtonClicked();
    void saveButtonClicked();
    void okButtonClicked();

protected:

protected slots:

private:
	char hwaddr[20];

private:
	char * read_hwaddr();

};

#endif // TMAINFORM_H
