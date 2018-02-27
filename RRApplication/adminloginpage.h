#ifndef ADMINLOGINPAGE_H
#define ADMINLOGINPAGE_H
#include "Camera.hpp"
#include <QDialog>
#include "room.h"
#include "adminconfigureroom.h"
#include "addroom.h"
#include "removeroom.h"
#include "anglebutton.h"
//extern std::vector <room>Allroom;
namespace Ui {
class adminloginpage;
}

class adminloginpage : public QDialog
{
    Q_OBJECT

public:
    explicit adminloginpage(QWidget *parent = 0);
    ~adminloginpage();

private slots:

    //void closeEvent(QCloseEvent *event);
    void on_videostream_clicked();
    int DoMotionDetection();



    void on_addroom_clicked();

    void on_removeroom_clicked();



    void on_logout_clicked();

    void on_cameraconfigure_clicked();

private:
    Ui::adminloginpage *ui;
};

#endif // ADMINLOGINPAGE_H
