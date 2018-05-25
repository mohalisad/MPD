#ifndef UIASSIST_H
#define UIASSIST_H

#include "qfont.h"

#if defined(__APPLE__)||defined(__MACH__)
    #define PATH (getPath()+"a.mpd").c_str()
    std::string getPath();
#else
    #define PATH "a.mpd"
#endif

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
