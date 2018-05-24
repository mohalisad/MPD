#include "readform.h"
#include "ui_readform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"

#include "qdebug.h"

ReadForm::ReadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadForm)
{
    ui->setupUi(this);
    setFont(UIAssist::yekan());
    ui->groupBox->setFont(UIAssist::yekan());
    ui->groupBox_2->setFont(UIAssist::yekan());
    setLayoutDirection(Qt::RightToLeft);

    diary.readFromText(readAllFromFile("a.mpd"));
    index=0;
    refreshUI();
}
void ReadForm::setButtonDisable()
{
    if(index<0)index=0;
    if(index>diary.size()-1)index=diary.size()-1;
    ui->prevBut->setDisabled(index==0);
    ui->nextBut->setDisabled(index+1==diary.size());

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
    ui->date->setText(diary[index]->getDate().c_str());
    ui->number->setText(QString::number(diary[index]->getNumber()));
    ui->textBrowser->setPlainText(diary[index]->getText().c_str());
    ui->textBrowser->setAlignment(Qt::AlignJustify);
}

void ReadForm::on_cancelBut_clicked()
{
    close();
}
