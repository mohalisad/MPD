#include "uiassist.h"
#include "qstring.h"
#include "qfontdatabase.h"
#include "strtoken.h"

#include "qdebug.h"

#define ENGLISH_NUMBERS "0123456789"
#define PERSIAN_NUMBERS "۰۱۲۳۴۵۶۷۸۹"

bool UIAssist::yekanSet=false;
int UIAssist::yekanID;
QString UIAssist::persianNumbers(PERSIAN_NUMBERS);
QString UIAssist::englishNumbers(ENGLISH_NUMBERS);

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
    for(int i=0;i<((int)tokens.size())-1;i++){
        retu+=tokens[i]+"</p><p align=\"justify\">";
    }
    retu+=tokens[tokens.size()-1]+"</p>";
    return QString(retu.c_str());
}

QString UIAssist::numConverter(QString input,bool fromPersianToEnglish){
    int index;
    for(int i=0;i<input.size();i++){
        if(fromPersianToEnglish){
            index=persianNumbers.indexOf(input[i]);
            if(index!=-1)input[i]=englishNumbers[index];
        }else{
            index=englishNumbers.indexOf(input[i]);
            if(index!=-1)input[i]=persianNumbers[index];
        }
    }
    return input;
}
bool UIAssist::digitValid(QChar input){
    return (englishNumbers.indexOf(input)+persianNumbers.indexOf(input))!=-2;
}
