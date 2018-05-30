#ifndef DIGITVALIDATOR_H
#define DIGITVALIDATOR_H

#include "qvalidator.h"
#include "uiassist.h"
class digitValidator:public QValidator{
    Q_OBJECT
private:
    QString otherValid;
    bool checkOtherValid(QChar c) const;
public:
    explicit digitValidator(const QString &_otherValid,QObject*parent=nullptr);
    explicit digitValidator(QObject*parent=nullptr);
    virtual QValidator::State validate (QString & input, int & ) const;
};

#endif // DIGITVALIDATOR_H
