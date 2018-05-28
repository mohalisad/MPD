#include "changepassform.h"
#include "ui_changepassform.h"
#include "diary.h"
#include "codeassist.h"
#include "qthreadpool.h"
#include "strlib.h"
#include "uiassist.h"
#include "mainwindow.h"

ChangePassThread::ChangePassThread(ChangePassForm* _parent,std::string input):QObject(_parent),QRunnable(){
    cpfParent=_parent;
    newPass=input;
}
void ChangePassThread::run(){
    Diary diary;
    diary.readFromText(readAllFromFile(PATH));
    QObject::connect(this, SIGNAL(setProgress(int)), cpfParent, SLOT(setProgress(int)));
    QObject::connect(this, SIGNAL(endProgress()), cpfParent, SLOT(closeYourself()));
    for (unsigned int i=0;i<diary.size();i++){
        diary[i]->recrypt(newPass);
        emit setProgress((float)i*100/diary.size());
    }
    writeInFile(PATH,diary.getEncrypted());
    emit endProgress();
}

ChangePassForm::ChangePassForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePassForm)
{
    ui->setupUi(this);
    QWidget::setFixedSize(250,200);
    ui->progressBar->setFont(UIAssist::yekan());
    ui->pushButton->setFont(UIAssist::yekan());
}

ChangePassForm::~ChangePassForm()
{
    delete ui;
}

void ChangePassForm::setProgress(int input){
    ui->progressBar->setValue(input);
}
void ChangePassForm::closeYourself(){
    MainWindow *mw=new MainWindow();
    mw->show();
    close();
}

void ChangePassForm::on_pushButton_clicked()
{
    ChangePassThread *t=new ChangePassThread(this,ui->newPass->text().toStdString());
    QThreadPool::globalInstance()->start(t);
}
