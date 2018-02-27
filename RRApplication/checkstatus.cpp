#include "checkstatus.h"

checkstatus::checkstatus()
{

        numofroom = Allroom.size();

        createroomselectionBox();
     //   createtimeselectionBox();
        qDebug()<<"done creation";

        labels[0] = new QLabel(tr("Select a room"));
        QFont font = labels[0]->font();
        font.setPointSize(13);
        font.setBold(true);
        labels[0]->setFont(font);


        labels[1] =new QLabel(tr(""));

        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));



        mainLayout= new QVBoxLayout();

        mainLayout->addWidget(labels[0]);
       // mainLayout->addWidget(horizontalGroupBox);
        mainLayout->addWidget(horizontalGroupBox);
        mainLayout->addWidget(labels[1]);

        mainLayout->addWidget(buttonBox);

        //mainLayout->SetMaximumSize();
        setLayout(mainLayout);

        setWindowTitle(tr("Check current availablity"));

}
void checkstatus::createroomselectionBox(){

    horizontalGroupBox = new QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout;
    roomlist = new QComboBox();
    for (int i = 0; i < Allroom.size();i++){
         roomlist->addItem(QString::number(Allroom[i].getroomnumber()));
    }

      layout->addWidget(roomlist);
      buttons[0] = new QPushButton(tr("check"));
      connect(buttons[0], SIGNAL (released()),this, SLOT (handleButton0()));
      layout->addWidget(buttons[0]);
      horizontalGroupBox->setLayout(layout);
      //qDebug()<<"done creation room selec";

}
void checkstatus::handleButton0(){
    int info;

   // startlist->clear();
    int roomid = (roomlist->currentText()).toInt();
    room temproom;
    int i=0;
    //qDebug()<<Allroom[0].getroomnumber();
    for (; i < Allroom.size(); i++){
        if (Allroom[i].getroomnumber() == roomid){
            temproom = Allroom[i];
            //roompos = i;
            break;
        }
    }
    if (i == Allroom.size()){
        qDebug()<<i;
        //alert
    }
    else {
        int currenhr = QTime::currentTime().hour();
        int num;
        if (num = temproom.getcamera()->GetPeopleCount()){
            qDebug()<<num;

        }

        if (temproom.getavailability(currenhr)){
            int i= currenhr;
            for (; i< 24;i++){
                if (!temproom.getavailability(i))
                    break;
            }
            QString text = QString("This room is available until %1").arg(i);
            labels[1]->setText(text);

        }
        else {
            QString text = QString("This room currently unavailable");
            labels[1]->setText(text);

        }

         mainLayout->update();


     }



}
