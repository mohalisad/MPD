#include "editorform.h"
#include "ui_editorform.h"
#include "uiassist.h"
#include "digitvalidator.h"
#include "date.h"

EditorForm::EditorForm(int entryNumber,int suggestNumber,QString date,QString text,ReadForm *parent) :
    QWidget(0),
    ui(new Ui::EditorForm)
{
    ui->setupUi(this);
    setFont(UIAssist::yekan());
    ui->groupBox->setFont(UIAssist::yekan());
    ui->groupBox_2->setFont(UIAssist::yekan());
    ui->textEdit->setAlignment(Qt::AlignJustify);
    ui->textEdit->setFont(UIAssist::yekan());

    ui->date->setValidator(new digitValidator("/"));
    ui->number->setValidator(new digitValidator());

    ui->number->setText(QString::number(entryNumber));
    suggested=suggestNumber;
    ui->date->setText(date);
    ui->textEdit->setHtml(UIAssist::justify(text));
    myparent=parent;
    QObject::connect(this, SIGNAL(formOK(int,QString,QString)), myparent, SLOT(entryEdit(int,QString,QString)));
}

EditorForm::~EditorForm()
{
    delete ui;
}
QString EditorForm::getNumber(){
    return UIAssist::numConverter(ui->number->text());
}
QString EditorForm::getDate(){
    return UIAssist::numConverter(ui->date->text());
}
QString EditorForm::getText(){
    return ui->textEdit->toPlainText();
}
void EditorForm::on_suggestNumberBut_clicked()
{
    ui->number->setText(QString::number(suggested));
}

void EditorForm::on_cancelBut_clicked()
{
    myparent->show();
    close();
}

void EditorForm::on_okBut_clicked()
{
    emit formOK(getNumber().toInt(),getDate(),getText());
    myparent->show();
    close();
}

void EditorForm::on_dateNextButton_clicked()
{
    ui->date->setText(Date(getDate().toStdString()).next().toString().c_str());
}

void EditorForm::on_dateBeforeButton_clicked()
{
    ui->date->setText(Date(getDate().toStdString()).prev().toString().c_str());
}
