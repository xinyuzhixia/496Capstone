#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_UserLoginButton_clicked()
{
    QString userinfo = getuserinfo();
    QStringList pieces = userinfo.split( "," );
    //std::cout<<pieces[0].toStdString();
    //std::cout<<pieces[1].toStdString()<<"-----"<<std::endl;
    QString inputname = ui->usernameline->toPlainText();
    QString inputpwd = ui->userpwdline->text();
    ui->usernameline->clear();
    ui->userpwdline->clear();
    //std::cout<<inputname.toStdString();
    //std::cout<<inputpwd.toStdString()<<"------"<<std::endl;

    if (!QString::compare(inputname, pieces[0], Qt::CaseSensitive)&& !QString::compare(inputpwd, pieces[1], Qt::CaseSensitive)){

        userloginpage usr;

       // usr.show();
        usr.exec();
    }

    else {
        ui->alert->setStyleSheet("QLabel { color : red; }");
        ui->alert->setText("Invalid username or password!");
    }
}

void MainWindow::on_AdminLoginButton_clicked()
{
    QString admininfo = getadmininfo();
    QStringList pieces = admininfo.split( "," );
    QString inputname = ui->adminnameline->toPlainText();
    QString inputpwd = ui->adminpwdline->text();
    ui->adminnameline->clear();
    ui->adminpwdline->clear();
    if (inputname == pieces[0]&&inputpwd == pieces[1])
    {   //addroom* dialog = new addroom();
        //dialog->setModal(true);
        //int result = dialog->exec();
        adminloginpage admin;

        //admin.show();
        admin.exec();

     }
    else {
        ui->adminalert->setStyleSheet("QLabel { color : red; }");
        ui->adminalert->setText("Invalid username or password!");
    }

}
QString MainWindow::getuserinfo()
{
       QFile myFile(":/user.txt");
       myFile.open(QIODevice::ReadOnly);
       QTextStream textStream(&myFile);
       QString line = textStream.readLine();
       return line;


}
QString MainWindow::getadmininfo()
{

    QFile myFile(":/admin.txt");
    myFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&myFile);
    QString line = textStream.readLine();
    return line;
}
