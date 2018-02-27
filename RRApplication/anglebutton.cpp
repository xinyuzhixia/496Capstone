#include "anglebutton.h"
#include "ui_anglebutton.h"
#include <QtWidgets>
anglebutton::anglebutton(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::anglebutton)
{
    ui->setupUi(this);
    roompos = -1;
    int i = 0;
    for (; i < Allroom.size();i++){
        ui->comboBox->addItem(QString::number(Allroom[i].getroomnumber()));
    }
    connect(ui->ok,SIGNAL(clicked(bool)), SLOT( setroom() ));
}

anglebutton::~anglebutton()
{
    delete ui;
}
void anglebutton::setroom() {

    roompos = ui->comboBox->currentIndex();
    qDebug()<<roompos;

}
void anglebutton::on_right_clicked()
{
    if (roompos!=-1){
        room curr = Allroom[roompos];
        curr.getcamera()->AdjustCameraAngle(6);
    }
}

void anglebutton::on_up_clicked()
{
    if (roompos!=-1){
        room curr = Allroom[roompos];
        curr.getcamera()->AdjustCameraAngle(0);
    }
}

void anglebutton::on_left_clicked()
{
    if (roompos!=-1){
        room curr = Allroom[roompos];
        curr.getcamera()->AdjustCameraAngle(4);
    }
}

void anglebutton::on_down_clicked()
{
    if (roompos!=-1){
        room curr = Allroom[roompos];
        curr.getcamera()->AdjustCameraAngle(2);
    }

}
