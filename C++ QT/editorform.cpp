#include "editorform.h"
#include "ui_editorform.h"
#include "uiassist.h"
#include "digitvalidator.h"
#include "date.h"
#include "exception.h"

EditorForm::EditorForm(int entryNumber,int suggestNumber,QString date,QString text,PersonState mood,ReadForm *parent) :
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
    setMood(mood);
    myparent=parent;
    QObject::connect(this, SIGNAL(formOK(int,QString,QString,PersonState)), myparent, SLOT(entryEdit(int,QString,QString,PersonState)));
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
PersonState EditorForm::getMood(){
    if(ui->sadeRadio->isChecked())return PS_SADE;
    if(ui->tajobRadio->isChecked())return PS_TAJOB;
    if(ui->afsordeRadio->isChecked())return PS_AFSORDE;
    if(ui->asabiRadio->isChecked())return PS_ASABI;
    if(ui->khkhoshalRadio->isChecked())return PS_KHKHOSHAL;
    if(ui->khoshalRadio->isChecked())return PS_KHOSHAL;
    if(ui->narahatRadio->isChecked())return PS_NARAHAT;
    if(ui->khnarahatRadio->isChecked())return PS_KHNARAHAT;
    return PS_SADE;
}
void EditorForm::setMood(PersonState mood){
    switch (mood) {
    case PS_SADE:
        ui->sadeRadio->setChecked(true);
        break;
    case PS_TAJOB:
        ui->tajobRadio->setChecked(true);
        break;
    case PS_AFSORDE:
        ui->afsordeRadio->setChecked(true);
        break;
    case PS_ASABI:
        ui->asabiRadio->setChecked(true);
        break;
    case PS_KHKHOSHAL:
        ui->khkhoshalRadio->setChecked(true);
        break;
    case PS_KHOSHAL:
        ui->khoshalRadio->setChecked(true);
        break;
    case PS_NARAHAT:
        ui->narahatRadio->setChecked(true);
        break;
    case PS_KHNARAHAT:
        ui->khnarahatRadio->setChecked(true);
        break;
    }
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
    emit formOK(getNumber().toInt(),getDate(),getText(),getMood());
    myparent->show();
    close();
}

void EditorForm::on_dateNextButton_clicked()
{
    try{
        ui->date->setText(Date(getDate().toStdString()).next().toString().c_str());
    }catch(Exception){}
}

void EditorForm::on_dateBeforeButton_clicked()
{
    try{
        ui->date->setText(Date(getDate().toStdString()).prev().toString().c_str());
    }catch(Exception){}
}
