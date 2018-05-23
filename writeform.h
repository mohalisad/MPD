#ifndef WRITEFORM_H
#define WRITEFORM_H

#include <QWidget>

namespace Ui {
class writeform;
}

class writeform : public QWidget
{
    Q_OBJECT

public:
    explicit writeform(QWidget *parent = 0);
    ~writeform();

private:
    Ui::writeform *ui;
};

#endif // WRITEFORM_H
