#include "writeform.h"
#include "ui_writeform.h"
#include "uiassist.h"
#include "strlib.h"
#include "date.h"

writeform::writeform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writeform)
{
    ui->setupUi(this);
    setFont(uiassist::yekan());
    ui->groupBox->setFont(uiassist::yekan());
    ui->groupBox_2->setFont(uiassist::yekan());
    setLayoutDirection(Qt::RightToLeft);
}

writeform::~writeform()
{
    delete ui;
}

void writeform::on_cancelBut_clicked()
{
    close();
}

void writeform::on_okBut_clicked()
{
    writeInFile("a.mpd",diary.getEncrypted());
}

void writeform::on_nextBut_clicked()
{
    diary.addEntry(ui->number->text().toInt(),new Date(ui->date->text().toStdString()),ui->textEdit->toPlainText().toStdString());
}

void writeform::on_dateNowButton_clicked()
{
    ui->date->setText(Date().toString().c_str());
}

void writeform::on_dateNextButton_clicked()
{
    ui->date->setText(Date(ui->date->text().toStdString()).next().toString().c_str());
}

void writeform::on_dateBeforeButton_clicked()
{
    ui->date->setText(Date(ui->date->text().toStdString()).prev().toString().c_str());
}
