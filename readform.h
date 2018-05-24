#ifndef READFORM_H
#define READFORM_H

#include <QWidget>
#include "diary.h"

namespace Ui {
class ReadForm;
}

class ReadForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReadForm(QWidget *parent = 0);
    ~ReadForm();

private slots:
    void on_prevBut_clicked();

    void on_nextBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::ReadForm *ui;
    int index;
    Diary diary;
    void setButtonDisable();
    void refreshUI();
};

#endif // READFORM_H
