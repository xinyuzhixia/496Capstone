#ifndef ANGLEBUTTON_H
#define ANGLEBUTTON_H

#include <QDialog>
#include "common.h"
namespace Ui {
class anglebutton;
}

class anglebutton : public QDialog
{
    Q_OBJECT

public:
    explicit anglebutton(QWidget *parent = 0);
    ~anglebutton();

private slots:
    void on_right_clicked();

    void on_up_clicked();

    void on_left_clicked();

    void on_down_clicked();
    void setroom();
private:
    int roompos;
    Ui::anglebutton *ui;
};

#endif // ANGLEBUTTON_H
