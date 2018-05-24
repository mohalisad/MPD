#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfont.h"
#include "qfontdatabase.h"
#include "writeform.h"
#include "readform.h"
#include "uiassist.h"
#include "entry.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setFixedSize(200,140);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->but1->setFont(uiassist::yekan());
    ui->but2->setFont(uiassist::yekan());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_but2_clicked()
{
    Entry::setUserKey(ui->lineEdit->text().toStdString());
    WriteForm *wf=new WriteForm();
    wf->show();
    close();
}

void MainWindow::on_but1_clicked()
{
    Entry::setUserKey(ui->lineEdit->text().toStdString());
    ReadForm *rf=new ReadForm();
    rf->show();
    close();
}
