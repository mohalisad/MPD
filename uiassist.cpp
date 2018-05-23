#include "uiassist.h"
#include "qstring.h"
#include "qfontdatabase.h"

uiassist::uiassist(){}

QFont uiassist::yekan(){
    int id = QFontDatabase::addApplicationFont(":/fonts/yekan.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont fon(family,13);
    fon.setPixelSize(16);
    return fon;
}
