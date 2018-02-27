#ifndef ADMINCONFIGUREROOM_H
#define ADMINCONFIGUREROOM_H

#include <QDialog>
#include <QtWidgets>
namespace Ui {
class adminconfigureroom;
}

class adminconfigureroom : public QDialog
{
    Q_OBJECT

public:
    explicit adminconfigureroom(QWidget *parent = 0);
    ~adminconfigureroom();

private slots:

    void createaddroominfo();
    void on_addroom_clicked();


private:
    Ui::adminconfigureroom *ui;


};

#endif // ADMINCONFIGUREROOM_H
