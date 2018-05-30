#include "writeform.h"
#include "ui_writeform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"
#include "codeassist.h"
#include "mainwindow.h"
#include "digitvalidator.h"

WriteForm::WriteForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteForm)
{
    ui->setupUi(this);
    setFont(UIAssist::yekan());
    ui->groupBox->setFont(UIAssist::yekan());
    ui->groupBox_2->setFont(UIAssist::yekan());
    ui->textEdit->setAlignment(Qt::AlignJustify);
    ui->textEdit->setFont(UIAssist::yekan());

    ui->date->setValidator(new digitValidator("/"));
    ui->number->setValidator(new digitValidator());

    diary.readFromText(readAllFromFile(PATH));
}

WriteForm::~WriteForm()
{
    delete ui;
}
QString WriteForm::getNumber(){
    return UIAssist::numConverter(ui->number->text());
}
QString WriteForm::getDate(){
    return UIAssist::numConverter(ui->date->text());
}
QString WriteForm::getText(){
    return ui->textEdit->toPlainText();
}


void WriteForm::on_cancelBut_clicked()
{
    MainWindow *mw=new MainWindow();
    mw->show();
    close();
}

void WriteForm::on_okBut_clicked()
{
    writeInFile(PATH,diary.getEncrypted());
    MainWindow *mw=new MainWindow();
    mw->show();
    close();
}

void WriteForm::on_nextBut_clicked()
{
    diary.addEntry(getNumber().toInt(),new Date(getDate().toStdString()),getText().toStdString());
    on_dateNextButton_clicked();
    on_autoincbut_clicked();
    ui->textEdit->setText("");
    ui->textEdit->setAlignment(Qt::AlignJustify);
    ui->textEdit->setFont(UIAssist::yekan());
}

void WriteForm::on_dateNowButton_clicked()
{
    ui->date->setText(Date().toString().c_str());
}

void WriteForm::on_dateNextButton_clicked()
{
    ui->date->setText(Date(getDate().toStdString()).next().toString().c_str());
}

void WriteForm::on_dateBeforeButton_clicked()
{
    ui->date->setText(Date(getDate().toStdString()).prev().toString().c_str());
}

void WriteForm::on_autoincbut_clicked()
{
    ui->number->setText(QString::number(diary.size()+1));
}
