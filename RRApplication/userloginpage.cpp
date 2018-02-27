#include "userloginpage.h"
#include "ui_userloginpage.h"

userloginpage::userloginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userloginpage)
{
    ui->setupUi(this);
    //QPushButton *button = new QPushButton("close", this);
       connect(ui->logout, SIGNAL(clicked()), this, SLOT(close()));

}

userloginpage::~userloginpage()
{
    delete ui;
}

void userloginpage::on_bookroom_clicked()
{
    bookroom* dialog = new bookroom();
    dialog->setModal(true);

    int result = dialog->exec();
    if (result){
        QStringList roominfo = dialog->getinfo();
        int roompos = roominfo[3].toInt();
        int start = roominfo[1].toInt();
        int end = roominfo[2].toInt();
        //int roomid = roominfo[0].toInt();
        for (int i = start; i < end; i++)
        {
            Allroom[roompos].updateavailability(i,false);
        }

    }
}

void userloginpage::on_cancelroom_clicked()
{

}

void userloginpage::on_checkstatus_clicked()
{
    checkstatus* dialog = new checkstatus();
    dialog->setModal(true);
    dialog->exec();
}

void userloginpage::on_logout_clicked()
{

}
