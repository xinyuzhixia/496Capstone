#include "addroom.h"

#include <QtWidgets>



addroom::addroom()
{
    //createMenu();
    //createHorizontalGroupBox();
    createGridGroupBox();
    //createFormGroupBox();



    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(gridGroupBox);

    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Edit room information"));
}

QStringList addroom::getinfo(){
    QStringList info;
    info<<lineEdits[0]->text()<< lineEdits[1]->text()<<lineEdits[2]->text()<<lineEdits[3]->text()<<lineEdits[4]->text();
    return info;
}

void addroom::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("room information"));
    QGridLayout *layout = new QGridLayout;


        labels[0] = new QLabel(tr("room number:"));
        lineEdits[0] = new QLineEdit;
        layout->addWidget(labels[0], 1, 0);
        layout->addWidget(lineEdits[0], 1, 1);
        labels[1] = new QLabel(tr("camera IP:"));
        lineEdits[1] = new QLineEdit;
        layout->addWidget(labels[1], 2, 0);
        layout->addWidget(lineEdits[1], 2, 1);
        labels[2] = new QLabel(tr("port number:"));
        lineEdits[2] = new QLineEdit;
        layout->addWidget(labels[2], 3, 0);
        layout->addWidget(lineEdits[2], 3, 1);
        labels[3] = new QLabel(tr("camera username:"));
        lineEdits[3] = new QLineEdit;
        layout->addWidget(labels[3], 4, 0);
        layout->addWidget(lineEdits[3], 4, 1);
        labels[4] = new QLabel(tr("camera password:"));
        lineEdits[4] = new QLineEdit;
        layout->addWidget(labels[4], 5, 0);
        layout->addWidget(lineEdits[4], 5, 1);
   // layout->addWidget(smallEditor, 0, 2, 4, 1);

    layout->setColumnStretch(0, 10);
    layout->setColumnStretch(1, 20);
    gridGroupBox->setLayout(layout);
}

