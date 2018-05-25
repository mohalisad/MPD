#include "readform.h"
#include "ui_readform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"
#include "qtimer.h"
#include "codeassist.h"
#include "mainwindow.h"

ReadForm::ReadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadForm)
{
    ui->setupUi(this);
    setFont(UIAssist::yekan());
    ui->groupBox->setFont(UIAssist::yekan());
    ui->groupBox_2->setFont(UIAssist::yekan());
    setLayoutDirection(Qt::RightToLeft);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
    timer->start(1000);
    updateClock();

    diary.readFromText(readAllFromFile(PATH));
    index=0;
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
        ui->date->setText(diary[index]->getDate().c_str());
        ui->dayOfWeek->setText(Date(diary[index]->getDate()).getDayOfWeek().c_str());
        ui->number->setText(QString::number(diary[index]->getNumber())+"/"+QString::number(diary.size()));
        ui->textBrowser->setHtml(UIAssist::justify(diary[index]->getText().c_str()));
        repaint();
    }
}

void ReadForm::on_cancelBut_clicked()
{
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
    index=ui->goNumber->text().toInt()-1;
    refreshUI();
}
