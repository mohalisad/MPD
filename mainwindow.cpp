#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfont.h"
#include "qfontdatabase.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setFixedSize(200,180);

    int id = QFontDatabase::addApplicationFont(":/fonts/naz.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont naz(family,20);
    ui->but1->setFont(naz);
    ui->but2->setFont(naz);
}

MainWindow::~MainWindow()
{
    delete ui;
}
