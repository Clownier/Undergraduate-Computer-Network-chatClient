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
        qDebug()<<"login success!";
        initListWidget();
    }
    else
        QTimer::singleShot(0, this, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
    mChatClient.close();
}
QString MainWindow::recvInfo(){
    QString res;
    while(true){
        QString ack;
        while(ack.length()==0){
            ack = mChatClient.Qrecv();
        }
        qDebug()<<"ack = "<<ack<<"\n";
        QJsonParseError *error = new QJsonParseError;
        QJsonArray array = QJsonDocument::fromJson(ack.toLatin1(),error).array();
        if(array.at(0).toInt() == 258){
            res.append(array.at(1).toString());
        }else if(array.at(0).toInt() == 259){
            res.append(array.at(1).toString());
            break;
        }
    }
    return res;
}

void MainWindow::initListWidget(){
    QString Info = recvInfo();
    userList=ui->userListWidget;
    QStringList strlist = Info.split("#");
    QString info = strlist.at(0);
    userList->addItems(info.split(";"));
    MyName = strlist.at(1);
}

void MainWindow::on_userListWidget_currentTextChanged(const QString &currentText)
{
    ui->widgetChat->clear();
    qDebug()<<currentText.toStdString().data()<<"is clicked!";
    ui->textEditSnd->setText(currentText);
}

void MainWindow::on_sendText_clicked()
{
    ui->widgetChat->addItem(ui->textEditSnd->toPlainText(),0);
}
