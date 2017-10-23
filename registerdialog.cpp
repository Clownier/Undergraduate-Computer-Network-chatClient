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
    QJsonArray qJsonArr;
    qJsonArr.insert(0,regEmail);
    qJsonArr.insert(1,regNikeName);
    qJsonArr.insert(2,regPassword);
    qJsonArr.insert(3,regRePassword);
    qJsonArr.insert(4,regSecReq);
    qJsonArr.insert(5,regSecAns);

    QJsonDocument document;
    document.setArray(qJsonArr);

    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
}

void registerDialog::on_cancelBut_clicked()
{

}
