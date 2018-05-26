#ifndef UIASSIST_H
#define UIASSIST_H

#include "qfont.h"
#include "qstring.h"

class UIAssist
{
private:
    UIAssist();
    static bool yekanSet;
    static int yekanID;
    static QString persianNumbers;
    static QString englishNumbers;
public:
    static QFont yekan();
    static QString justify(QString input);
    static QString numConverter(QString input,bool fromPersianToEnglish=true);
    static bool digitValid(QChar input);
};
#endif // UIASSIST_H
