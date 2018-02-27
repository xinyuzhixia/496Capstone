#ifndef BOOKROOM_H
#define BOOKROOM_H
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

class bookroom : public QDialog
{
    Q_OBJECT

public:
    bookroom();
    QStringList getinfo();
private:
    int roompos;

    void createroomselectionBox();
    void createtimeselectionBox();
    QLabel *labels[3];
    enum { NumGridRows = 1, NumButtons = 3 };
    QLineEdit *lineEdits[NumGridRows];

    QComboBox* roomlist;
    QComboBox* startlist;
    QComboBox* endlist;
    QGroupBox *horizontalGroupBox;
    QGroupBox *horizontaltimeBox;
    QVBoxLayout *mainLayout;
   // QLabel *labels[NumGridRows];

    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;
public slots:
     void handleButton0();
     void getendtime();
};


#endif // BOOKROOM_H
