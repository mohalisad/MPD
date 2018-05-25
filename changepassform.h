#ifndef CHANGEPASSFORM_H
#define CHANGEPASSFORM_H

#include <string>
#include <QWidget>
#include "qrunnable.h"

namespace Ui {
class ChangePassForm;
}

class ChangePassForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePassForm(QWidget *parent = 0);
    ~ChangePassForm();
public slots:
    void setProgress(int input);
    void closeYourself();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePassForm *ui;
};

class ChangePassThread:public QObject,public QRunnable{
    Q_OBJECT
private:
    std::string newPass;
    ChangePassForm* cpfParent;
signals:
    void setProgress(int input);
    void endProgress();
public:
    ChangePassThread(ChangePassForm* _parent,std::string input);
    virtual ~ChangePassThread() {}
    void run();

};
#endif // CHANGEPASSFORM_H
