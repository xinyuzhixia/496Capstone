#ifndef REMOVEROOM_H
#define REMOVEROOM_H

#include <QDialog>
#include <QStringList>
#include <QComboBox>
#include "common.h"
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

class removeroom : public QDialog
{
    Q_OBJECT

public:
    removeroom();
    QString getinfo();
private:

    void createGridGroupBox();


    enum { NumGridRows = 5, NumButtons = 2 };
    QGroupBox *gridGroupBox;
    QDialogButtonBox *buttonBox;

    QPushButton *buttons[NumButtons];
    QComboBox* roomlist;


};


#endif // REMOVEROOM_H
