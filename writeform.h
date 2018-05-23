#ifndef WRITEFORM_H
#define WRITEFORM_H

#include <QWidget>
#include "diary.h"

namespace Ui {
class writeform;
}

class writeform : public QWidget
{
    Q_OBJECT

public:
    explicit writeform(QWidget *parent = 0);
    ~writeform();

private slots:
    void on_cancelBut_clicked();

    void on_okBut_clicked();

    void on_nextBut_clicked();

private:
    Ui::writeform *ui;
    Diary diary;
};

#endif // WRITEFORM_H
