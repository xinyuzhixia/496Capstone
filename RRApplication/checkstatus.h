#ifndef CHECKSTATUS_H
#define CHECKSTATUS_H
#include <QComboBox>
#include "common.h"
#include <QDialog>
#include <QStringList>
#include <QtWidgets>
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

class checkstatus : public QDialog
{
    Q_OBJECT

public:
    checkstatus();
    QStringList getinfo();
private:
    int numofroom;

    void createroomselectionBox();

    QLabel *labels[3];
    enum { NumGridRows = 1, NumButtons = 3 };
    QLineEdit *lineEdits[NumGridRows];

    QComboBox* roomlist;

    QGroupBox *horizontalGroupBox;
    QGroupBox *horizontaltimeBox;
    QVBoxLayout *mainLayout;
   // QLabel *labels[NumGridRows];

    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;
public slots:
     void handleButton0();

};


#endif // CHECKSTATUS_H
