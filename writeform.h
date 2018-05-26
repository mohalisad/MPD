#ifndef WRITEFORM_H
#define WRITEFORM_H

#include <QWidget>
#include "diary.h"

namespace Ui {
class WriteForm;
}

class WriteForm : public QWidget
{
    Q_OBJECT

public:
    explicit WriteForm(QWidget *parent = 0);
    ~WriteForm();

private slots:
    void on_cancelBut_clicked();

    void on_okBut_clicked();

    void on_nextBut_clicked();

    void on_dateNowButton_clicked();

    void on_dateNextButton_clicked();

    void on_dateBeforeButton_clicked();

    void on_autoincbut_clicked();

private:
    Ui::WriteForm *ui;
    Diary diary;
    QString getNumber();
    QString getDate();
    QString getText();
};

#endif // WRITEFORM_H
