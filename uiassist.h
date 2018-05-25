#ifndef UIASSIST_H
#define UIASSIST_H

#include "qfont.h"

class UIAssist
{
private:
    UIAssist();
    static bool yekanSet;
    static int yekanID;
public:
    static QFont yekan();
    static QString justify(QString input);
};

#endif // UIASSIST_H
