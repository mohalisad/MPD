#include "uiassist.h"
#include "qstring.h"
#include "qfontdatabase.h"
#include "strtoken.h"

#include "qdebug.h"

#if defined(__APPLE__)||defined(__MACH__)
#include <mach-o/dyld.h>
#endif

bool UIAssist::yekanSet=false;
int UIAssist::yekanID;

UIAssist::UIAssist(){}

QFont UIAssist::yekan(){
    int id;
    if(!yekanSet){
        id=QFontDatabase::addApplicationFont(":/fonts/yekan.ttf");
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
    StringTokenizer tokens(input.toStdString(),"\n\r");
    std::string retu="<p align=\"justify\">";
    for(int i=0;i<tokens.size()-1;i++){
        retu+=tokens[i]+"</p><p align=\"justify\">";
    }
    retu+=tokens[tokens.size()-1]+"</p>";
    return QString(retu.c_str());
}
std::string getPath(){
    char buffer[1024];
    unsigned int size;
    std::string retu="/";
    _NSGetExecutablePath(buffer, &size);
    _NSGetExecutablePath(buffer, &size);
    StringTokenizer tokens(std::string(buffer),"/");
    for(int i=0;i<(int)tokens.size()-4;i++){

        retu+=tokens[i]+"/";
    }
    return retu;
}
