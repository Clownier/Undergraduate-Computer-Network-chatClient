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
        MyUuid = *userName;
        qDebug()<<MyUuid.toStdString().data();
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
    QString recv;
    while(1){
        recv = mChatClient.Qrecv();
        if(recv.length()==0)
            continue;
        //TODO carry recv
    }
}

void MainWindow::on_userListWidget_currentTextChanged(const QString &currentText)
{
    //点击用户，将界面刷新
    //TODO 将用户id传到服务器,返回用户是否在线
    ui->widgetChat->clear();
    qDebug()<<currentText.toStdString().data()<<"is clicked!";
    //ui->textEditSnd->setText(currentText);
    ui->currentUser->setText(currentText);
}

void MainWindow::on_sendText_clicked()
{
    //将消息发送到服务器
    QString currID = ui->currentUser->text();
    int  index = currID.indexOf("{");
    currID = currID.mid(index,currID.length()-index);
    qDebug()<<currID;
    QString send = ui->textEditSnd->toPlainText();
    ui->widgetChat->addItem(send,2);
    QJsonArray arr;arr.insert(0,584);
    arr.insert(1,currID);arr.insert(2,MyUuid);
    arr.insert(3,send);QJsonDocument doc;
    doc.setArray(arr);
    send = doc.toJson(QJsonDocument::Compact);
    qDebug()<<send;
    mChatClient.Qsend(send);
    ui->widgetChat->addItem("this is once",1);
}
