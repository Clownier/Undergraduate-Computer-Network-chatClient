#include "registerdialog.h"
#include "ui_registerdialog.h"

registerDialog::registerDialog(Chat_Client &client, QWidget *parent) :
    QDialog(parent),
    mChatClient(client),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    ui->reg_password->setEchoMode(QLineEdit::Password);
    ui->reg_repassword->setEchoMode(QLineEdit::Password);
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_registerBut_clicked()
{
    regEmail = ui->reg_email->text();
    regNikeName = ui->reg_nikeName->text();
    regPassword = ui->reg_password->text();
    regRePassword = ui->reg_repassword->text();
    regSecReq = ui->reg_securityReq->text();
    regSecAns = ui->reg_securityAns->text();
    if(regPassword.length()<6){
        QMessageBox::critical(NULL, "critical", "the password is too easy", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    else if(regPassword != regRePassword){
        QMessageBox::critical(NULL, "critical", "please confirm the password", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }else{
        QJsonArray qJsonArr;
        qJsonArr.insert(0,600);//注册编码
        qJsonArr.insert(1,regNikeName);
        qJsonArr.insert(2,regEmail);
        qJsonArr.insert(3,regPassword);
        qJsonArr.insert(4,regSecReq);
        qJsonArr.insert(5,regSecAns);

        QJsonDocument document;
        document.setArray(qJsonArr);
        QString json_str =  document.toJson(QJsonDocument::Compact);
        mChatClient.Qsend(json_str);
        json_str.clear();
        while(json_str.length()==0){
            json_str = mChatClient.Qrecv();
        }
        QJsonParseError *error = new QJsonParseError;
        qJsonArr = QJsonDocument::fromJson(json_str.toLatin1(),error).array();
        if(qJsonArr.at(0).toInt() == 602){
            QMessageBox::critical(NULL, "critical", "your email has registered", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }else if(qJsonArr.at(0).toInt() == 601){
            QMessageBox::information(NULL,"information","register success!",QMessageBox::Yes , QMessageBox::Yes);
            accept();
        }
    }


}

void registerDialog::on_cancelBut_clicked()
{
    reject();
}
