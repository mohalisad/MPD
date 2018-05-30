#include "digitvalidator.h"

bool digitValidator::checkOtherValid(QChar c)const{
    return otherValid.indexOf(c)!=-1;
}

digitValidator::digitValidator(const QString& _otherValid, QObject *){
    otherValid=_otherValid;
}
digitValidator::digitValidator(QObject *){
    otherValid="";
}

digitValidator::State digitValidator::validate (QString & input, int & )const{
    if (input.isEmpty())
        return Acceptable;
    for(int i=0;i<input.size();i++){
        if(!checkOtherValid(input[i])&&!UIAssist::digitValid(input[i]))
            return Invalid;
    }
    return Acceptable;
}

