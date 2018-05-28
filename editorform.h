#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>
#include "readform.h"

namespace Ui {
class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT
signals:
    formOK(int number,QString date,QString text);
public:
    explicit EditorForm(int entryNumber,int suggestNumber,QString date,QString text,ReadForm *parent);
    ~EditorForm();
private slots:
    void on_suggestNumberBut_clicked();

    void on_cancelBut_clicked();

    void on_okBut_clicked();

    void on_dateBeforeButton_clicked();

    void on_dateNextButton_clicked();

private:
    Ui::EditorForm *ui;
    ReadForm *myparent;
    int suggested;
    QString getNumber();
    QString getDate();
    QString getText();
};

#endif // EDITORFORM_H
