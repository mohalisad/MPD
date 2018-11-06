#include "readform.h"
#include "ui_readform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"
#include "qtimer.h"
#include "codeassist.h"
#include "mainwindow.h"
#include "digitvalidator.h"
#include "editorform.h"
#include "exception.h"
#include "qmessagebox.h"

ReadForm::ReadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadForm)
{
    ui->setupUi(this);
    setFont(UIAssist::yekan());
    ui->groupBox->setFont(UIAssist::yekan());
    ui->groupBox_2->setFont(UIAssist::yekan());

    ui->goNumber->setValidator(new digitValidator());

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
    timer->start(1000);
    updateClock();

    diary.readFromText(readAllFromFile(PATH));

    index=0;
    isChanged=false;

    refreshUI();
}
void ReadForm::entryEdit(int number,QString date,QString text,PersonState mood){
    isChanged=true;
    diary[index]->setNumber(number);
    diary[index]->setDate(date.toStdString());
    diary[index]->setText(text.toStdString());
    diary[index]->setMood(mood);
    refreshUI();
}
void ReadForm::setButtonDisable()
{
    if(index<0)index=0;
    if(index>((int)diary.size())-1)index=(int)diary.size()-1;
    ui->prevBut->setDisabled(index==0);
    ui->nextBut->setDisabled((unsigned int)index+1==diary.size());

}

ReadForm::~ReadForm()
{
    delete ui;
}

void ReadForm::on_prevBut_clicked()
{
    index--;
    refreshUI();
}

void ReadForm::on_nextBut_clicked()
{
    index++;
    refreshUI();
}
void ReadForm::refreshUI(){
    setButtonDisable();
    if(diary.size()!=0){
        try{
            ui->date->setText(diary[index]->getDate().c_str());
            ui->dayOfWeek->setText(Date(diary[index]->getDate()).getDayOfWeek().c_str());
            ui->number->setText(QString::number(diary[index]->getNumber()));
            ui->indexNumber->setText(QString::number(index+1)+"/"+QString::number(diary.size()));
            ui->textBrowser->setHtml(UIAssist::justify(diary[index]->getText().c_str()));
            ui->mood->setText(get_moodstr(diary[index]->getMood()).c_str());
        }catch(Exception ex){
            QMessageBox msg;
            msg.setFont(UIAssist::yekan());
            msg.setText("فایل آسیب دیده است یا رمز فایل نادرست است.");
            msg.setIcon(QMessageBox::Critical);
            msg.exec();
            throw Exception("Wrong Entry");
        }
        repaint();
    }else{
        QMessageBox msg;
        msg.setFont(UIAssist::yekan());
        msg.setText("هیچ ورودی برای خواندن وجود ندارد.");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
        throw Exception("No Entry");
    }
}

void ReadForm::on_exitBut_clicked()
{
    if(isChanged)writeInFile(PATH,diary.getEncrypted());
    MainWindow *mw=new MainWindow();
    mw->show();
    close();
}
void ReadForm::updateClock(){
    ui->nowDate->setText(Date::now().c_str());
    ui->nowDayOfWeek->setText(Date().getDayOfWeek().c_str());
}

void ReadForm::on_goButton_clicked()
{
    index=UIAssist::numConverter(ui->goNumber->text()).toInt()-1;
    refreshUI();
}

void ReadForm::on_editBut_clicked()
{
    EditorForm *ef=new EditorForm(diary[index]->getNumber(),index+1,diary[index]->getDate().c_str(),diary[index]->getText().c_str(),diary[index]->getMood(),this);
    ef->show();
    hide();
}
