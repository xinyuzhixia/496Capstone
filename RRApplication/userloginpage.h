#ifndef USERLOGINPAGE_H
#define USERLOGINPAGE_H

#include <QDialog>
#include <QWidget>
#include <QCalendarWidget>
#include "room.h"
#include "bookroom.h"
#include "checkstatus.h"
extern std::vector <room>Allroom;
namespace Ui {
class userloginpage;
}

class userloginpage : public QDialog
{
    Q_OBJECT

public:
    explicit userloginpage(QWidget *parent = 0);
    ~userloginpage();

private slots:
    void on_bookroom_clicked();

    void on_cancelroom_clicked();

    void on_checkstatus_clicked();

    void on_logout_clicked();

private:
    Ui::userloginpage *ui;
};

#endif // USERLOGINPAGE_H
