#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include "clientsocket.h"
#include "registerdialog.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(Chat_Client &Client,QString *userName,QString *password,QWidget *parent = 0);
    ~loginDialog();

private slots:
    void on_forgetButton_2_clicked();

    void on_loginButton_2_clicked();

    void on_registerButton_2_clicked();

private:
    Ui::loginDialog *ui;
    QString *userName,*password;
    Chat_Client &mChatClient;
};

#endif // LOGINDIALOG_H
