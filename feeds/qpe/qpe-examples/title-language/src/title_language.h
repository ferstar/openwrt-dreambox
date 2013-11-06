#ifndef TMAINFORM_H
#define TMAINFORM_H

#include "title_language_base.h"
#include <qvariant.h>

#define EN false
#define CN true

class TMainForm : public TMainFormBase
{
    Q_OBJECT

public:
    TMainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel) : TMainFormBase(parent, name, fl), LanguageName(CN) {}
    ~TMainForm() {}

public slots:
    void cancelButtonClicked();
    void chineseButtonClicked();
    void englishButtonClicked();
    void okButtonClicked();

protected:

protected slots:

private:
    bool LanguageName;

};

#endif // TMAINFORM_H
