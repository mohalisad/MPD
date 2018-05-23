#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfont.h"
#include "qfontdatabase.h"
#include "writeform.h"
#include "uiassist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setFixedSize(200,140);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->but1->setFont(uiassist::yekan());
    ui->but2->setFont(uiassist::yekan());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_but2_clicked()
{
    writeform *wf=new writeform();
    wf->show();
    close();
}
