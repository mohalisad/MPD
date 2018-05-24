#include "writeform.h"
#include "ui_writeform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"

WriteForm::WriteForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteForm)
{
    ui->setupUi(this);
    setFont(uiassist::yekan());
    ui->groupBox->setFont(uiassist::yekan());
    ui->groupBox_2->setFont(uiassist::yekan());
    setLayoutDirection(Qt::RightToLeft);
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
    writeInFile("a.mpd",diary.getEncrypted());
}

void WriteForm::on_nextBut_clicked()
{
    diary.addEntry(ui->number->text().toInt(),new Date(ui->date->text().toStdString()),ui->textEdit->toPlainText().toStdString());
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
