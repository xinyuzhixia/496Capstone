#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userloginpage.h"
#include "adminloginpage.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_UserLoginButton_clicked();

    void on_AdminLoginButton_clicked();

private:
    Ui::MainWindow *ui;
    QString getuserinfo();
    QString getadmininfo();
};

#endif // MAINWINDOW_H
