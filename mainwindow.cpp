#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientsocket.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mChatClient.create();
    mChatClient.bind();
    mChatClient.connect();
    QString *userName = new QString;
    QString *password = new QString;
    loginDialog login(mChatClient,userName,password,this);
    login.setModal(true);
    if(login.exec() != QDialog::Accepted)
        qDebug()<<"error!";
//    sprintf(mChatClient.sendBuf,"userName:%s\tpassword:%s",userName->toUtf8().data(),password->toUtf8().data());
//    mChatClient.send();

//    for(int i =0;i<5;i++){
//        sprintf(mChatClient.sendBuf,"this is %d send!",i);
//        mChatClient.send();
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
    mChatClient.close();
}
