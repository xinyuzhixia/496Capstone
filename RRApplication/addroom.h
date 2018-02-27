#ifndef ADDROOM_H
#define ADDROOM_H

#include <QDialog>
#include <QStringList>
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

class addroom : public QDialog
{
    Q_OBJECT

public:
    addroom();
    QStringList getinfo();
private:

    void createGridGroupBox();



    enum { NumGridRows = 5, NumButtons = 2 };
    QLineEdit *lineEdits[NumGridRows];


    QGroupBox *gridGroupBox;
    QLabel *labels[NumGridRows];

    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

};

#endif
