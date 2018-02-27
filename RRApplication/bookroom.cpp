#include "bookroom.h"
#include <QtWidgets>


bookroom::bookroom()
{
    //createMenu();
    roompos = -1;
    createroomselectionBox();
    createtimeselectionBox();
    qDebug()<<"done creation";

    labels[0] = new QLabel(tr("Select a room"));
    QFont font = labels[0]->font();
    font.setPointSize(13);
    font.setBold(true);
    labels[0]->setFont(font);

    labels[1] = new QLabel(tr("Select start/end time"));
    QFont font1 = labels[1]->font();
    font.setPointSize(13);
    font.setBold(true);
    labels[1]->setFont(font);
    labels[2] = new QLabel(tr("Select end time"));
    QFont font2 = labels[2]->font();
    font.setPointSize(13);
    font.setBold(true);
    labels[2]->setFont(font);
   // const QSize BUTTON_SIZE = QSize(22, 22);

    //startlist = new QComboBox();
   // endlist = new QComboBox();


    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));



    mainLayout= new QVBoxLayout();

    mainLayout->addWidget(labels[0]);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(labels[1]);
    mainLayout->addWidget(horizontaltimeBox);
    mainLayout->addWidget(buttonBox);

    //mainLayout->SetMaximumSize();
    setLayout(mainLayout);

    setWindowTitle(tr("reserve"));
}
void bookroom::createroomselectionBox(){

    horizontalGroupBox = new QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout;
    roomlist = new QComboBox();
    for (int i = 0; i < Allroom.size();i++){
         roomlist->addItem(QString::number(Allroom[i].getroomnumber()));
    }

      layout->addWidget(roomlist);
      buttons[0] = new QPushButton(tr("ok"));
      connect(buttons[0], SIGNAL (released()),this, SLOT (handleButton0()));
      layout->addWidget(buttons[0]);
      horizontalGroupBox->setLayout(layout);
      qDebug()<<"done creation room selec";

}
void bookroom::handleButton0(){
    int info;

    startlist->clear();
    int roomid = (roomlist->currentText()).toInt();
    room temproom;
    int i=0;
    //qDebug()<<Allroom[0].getroomnumber();
    for (; i < Allroom.size(); i++){
        if (Allroom[i].getroomnumber() == roomid){
            temproom = Allroom[i];
            roompos = i;
            break;
        }
    }
    if (i == Allroom.size()){
        qDebug()<<i;
        //alert
    }
    else {

         for (int j = 0 ; j < 24; j++){
             bool m = temproom.getavailability(j);
             if (m){

                 qDebug()<<"starttime: "<<j;

                 startlist->addItem(QString::number(j));
             }
         }


         // QHBoxLayout *layout = new QHBoxLayout;
       //  layout->addWidget(startlist);
        // layout->addWidget(endlist);
        // delete horizontaltimeBox->layout();
         horizontaltimeBox->update();
         mainLayout->update();


     }



}
void bookroom::getendtime(){
    //delete horizontaltimeBox;
    //delete endlist;
   // endlist = new QComboBox();
    endlist->clear();

    room temproom = Allroom[roompos];
    int starthour = startlist->currentText().toInt();

    if (starthour != NULL) {
        for (int k = starthour+1; k < 24 ; k++){
             qDebug()<<"starthour"<<starthour;
             qDebug()<<"k:"<<k;
             bool tmp = temproom.getavailability(k);
             qDebug()<<temproom.getavailability(k);
            if (tmp){
                qDebug()<<"addendtime"<<k;
                endlist->addItem(QString::number(k));
            }
            else {
                break;
            }
        }
    }


    horizontaltimeBox->update();
    mainLayout->update();

}
void bookroom::createtimeselectionBox(){

    horizontaltimeBox = new QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout;
    startlist = new QComboBox();
    endlist = new QComboBox();
    connect(startlist,SIGNAL(currentIndexChanged(int)), SLOT( getendtime() ));

    layout->addWidget(startlist);
    layout->addWidget(endlist);
    horizontaltimeBox->setLayout(layout);

}
QStringList bookroom::getinfo(){
    QStringList info;
    info<<roomlist->currentText()<<startlist->currentText()<<endlist->currentText()<<QString::number(roompos);;
    return info;
}
