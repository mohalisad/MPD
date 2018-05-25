#include "writeform.h"
#include "ui_writeform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"
#include "codeassist.h"

WriteForm::WriteForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteForm)
{
    ui->setupUi(this);
    setFont(UIAssist::yekan());
    ui->groupBox->setFont(UIAssist::yekan());
    ui->groupBox_2->setFont(UIAssist::yekan());
    setLayoutDirection(Qt::RightToLeft);
    ui->textEdit->setAlignment(Qt::AlignJustify);
    ui->textEdit->setFont(UIAssist::yekan());

    diary.readFromText(readAllFromFile(PATH));
}

WriteForm::~WriteForm()
{
    delete ui;
}

void WriteForm::on_cancelBut_clicked()
{
    close();
}

void WriteForm::on_okBut_clicked()
{
    writeInFile(PATH,diary.getEncrypted());
    close();
}

void WriteForm::on_nextBut_clicked()
{
    diary.addEntry(ui->number->text().toInt(),new Date(ui->date->text().toStdString()),ui->textEdit->toPlainText().toStdString());
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
    ui->date->setText(Date(ui->date->text().toStdString()).next().toString().c_str());
}

void WriteForm::on_dateBeforeButton_clicked()
{
    ui->date->setText(Date(ui->date->text().toStdString()).prev().toString().c_str());
}

void WriteForm::on_autoincbut_clicked()
{
    ui->number->setText(QString::number(diary.size()+1));
}
