#include "uiassist.h"
#include "qstring.h"
#include "qfontdatabase.h"

bool UIAssist::yekanSet=false;
int UIAssist::yekanID;

UIAssist::UIAssist(){}

QFont UIAssist::yekan(){
    int id;
    if(!yekanSet){
        QFontDatabase::addApplicationFont(":/fonts/yekan.ttf");
        yekanID=id;
    }
    else id=yekanID;
    yekanSet=true;
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont fon(family,13);
    fon.setPixelSize(16);
    return fon;
}
QString UIAssist::justify(QString input){
    return "<p align=\"justify\">"+input+"</p>";
}

