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
    sprintf(mChatClient.sendBuf,"%s#*#*2461538790*#*#%s",userName->toUtf8().data(),password->toUtf8().data());
    mChatClient.send();
    //loginDialog::close();
    string ack = "000";
    while(ack.find("#*#*2461538790*#*#id:")==string::npos){
        ack = mChatClient.recv();
    }
    ack = ack.substr(21);
    qDebug()<<"ack = "<<ack.c_str()<<"\n";
    accept();
}


void loginDialog::on_registerButton_2_clicked()
{
    registerDialog dialog(mChatClient,this);
    dialog.setModal(true);
    if(dialog.exec() != QDialog::Accepted ){
        qDebug()<<"register error!";
    }
}
