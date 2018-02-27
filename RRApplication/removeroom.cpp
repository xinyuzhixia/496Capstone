#include "removeroom.h"

#include "addroom.h"

#include <QtWidgets>


removeroom::removeroom()
{
    //createMenu();
    //createHorizontalGroupBox();
    //createGridGroupBox();
    //createFormGroupBox();
    roomlist = new QComboBox();

    for (int i = 0; i < Allroom.size();i++){
         roomlist->addItem(QString::number(Allroom[i].getroomnumber()));
    }

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(roomlist);

    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("remove room"));
}

QString removeroom::getinfo(){
    QString info;
    info = roomlist->currentText();
    //info<<lineEdits[0]->text()<< lineEdits[1]->text()<<lineEdits[2]->text()<<lineEdits[3]->text()<<lineEdits[4]->text();
    return info;
}

