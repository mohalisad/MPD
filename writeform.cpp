#include "writeform.h"
#include "ui_writeform.h"

writeform::writeform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writeform)
{
    ui->setupUi(this);
}

writeform::~writeform()
{
    delete ui;
}
