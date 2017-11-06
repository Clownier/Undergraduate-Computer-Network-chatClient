#include "forgetdialog.h"
#include "ui_forgetdialog.h"

forgetDialog::forgetDialog(Chat_Client &client, QWidget *parent) :
    QDialog(parent),
    mChatClient(client),
    ui(new Ui::forgetDialog)
{
    ui->setupUi(this);
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    inputEmail = true;
}

forgetDialog::~forgetDialog()
{
    delete ui;
}

void forgetDialog::on_confrimBut_clicked()
{
    if(inputEmail){
        QString email = ui->editLine->text();
        QJsonArray arr;arr.insert(0,700);
        arr.insert(1,email);QJsonDocument doc;
        doc.setArray(arr);
        QString send = doc.toJson(QJsonDocument::Compact);
        mChatClient.Qsend(send);
        send.clear();
        while (send.length()==0) {
            send = mChatClient.Qrecv();
        }
        QJsonArray ack = QJsonDocument::fromJson(send.toLatin1(),NULL).array();
        if(ack.at(0).toInt() == 701){
            ui->label_1->setVisible(true);
            ui->label_2->setVisible(true);
            ui->label_2->setText(ack.at(1).toString());
            ans = ack.at(2).toString();
            Uuid = ack.at(3).toString();
            ui->label_3->setText("密保答案：");
            ui->confrimBut->setText("获取密码");
            inputEmail = false;
        }
        else{
            QMessageBox::critical(NULL, "critical", "your email is unfound!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
        ui->editLine->setText("");
    }else{
        if(ui->editLine->text() == ans){
            QJsonArray arr;arr.insert(0,710);
            arr.insert(1,Uuid);QJsonDocument doc;
            doc.setArray(arr);
            QString send = doc.toJson(QJsonDocument::Compact);
            mChatClient.Qsend(send);
            send.clear();
            while(send.length()==0)
                send = mChatClient.Qrecv();
            QJsonArray ack = QJsonDocument::fromJson(send.toLatin1(),NULL).array();
            send = "your password is ";
            send.append(ack.at(1).toString());
            QMessageBox::critical(NULL, "critical", send, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            accept();
        }else{
            QMessageBox::information(NULL, "critical", "your answer is error!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            reject();
        }
    }
}

void forgetDialog::on_cancelBut_clicked()
{
    reject();
}
