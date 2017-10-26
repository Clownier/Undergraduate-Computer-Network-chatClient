#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "clientsocket.h"
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
    if(login.exec() == QDialog::Accepted){
        initListWidget();
        qDebug()<<"login success!";
    }
    else
        QTimer::singleShot(0, this, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
    mChatClient.close();
}

void MainWindow::initListWidget(){
    string ack;
    while(ack.length()==0){
        ack = mChatClient.recv();
    }
    QJsonParseError *error = new QJsonParseError;
    QString qAck = QString::fromStdString(ack);
    QJsonArray array = QJsonDocument::fromJson(qAck.toLatin1(),error).array();
    userList=ui->userListWidget;
    if(array.at(0).toInt() == 258){
        QStringList strlist = array.at(1).toString().split("#");
        QString info = strlist.at(0);
        userList->addItems(info.split(";"));
        MyName = strlist.at(1);
    }
}

void MainWindow::on_userListWidget_currentTextChanged(const QString &currentText)
{
    Q_UNUSED(currentText);
}
