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
public slots:
    void entryEdit(int number,QString date,QString text);
private slots:
    void on_prevBut_clicked();

    void on_nextBut_clicked();

    void on_exitBut_clicked();

    void updateClock();

    void on_goButton_clicked();

    void on_editBut_clicked();

private:
    Ui::ReadForm *ui;
    int index;
    bool isChanged;
    Diary diary;
    void setButtonDisable();
    void refreshUI();
};

#endif // READFORM_H
