#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(Chat_Client &client,QString *Name, QString *Pass, QWidget *parent) :
    QDialog(parent), 
    ui(new Ui::loginDialog),
    mChatClient(client)
{
    ui->setupUi(this);
    ui->password_2->setEchoMode(QLineEdit::Password);
    userName = Name;
    password = Pass;
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_forgetButton_2_clicked()
{

}

void loginDialog::on_loginButton_2_clicked()
{
    *userName = ui->userName->text();
    *password = ui->password_2->text();
    QJsonArray array;
    array.insert(0,0);
    array.insert(1,*userName);
    array.insert(2,*password);
    QJsonDocument document;
    document.setArray(array);
    QByteArray byte = document.toJson(QJsonDocument::Compact);
    string login = byte.toStdString();
    sprintf(mChatClient.sendBuf,"%s",login.c_str());
    mChatClient.send();
    string ack;
    while(ack.length()==0){
        ack = mChatClient.recv();
    }
    QJsonParseError *error = new QJsonParseError;
    QString qAck = QString::fromStdString(ack);
    array = QJsonDocument::fromJson(qAck.toLatin1(),error).array();
    if(array.at(0).toInt() == 1){
        qDebug()<<array.at(1).toString();
        accept();
    }else{
        qDebug()<<array.at(1).toString();
        QMessageBox::critical(NULL, "critical", array.at(1).toString(), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        reject();
    }
}


void loginDialog::on_registerButton_2_clicked()
{
    registerDialog dialog(mChatClient,this);
    dialog.setModal(true);
    if(dialog.exec() != QDialog::Accepted ){
        qDebug()<<"register error!";
    }
}
