#ifndef FORGETDIALOG_H
#define FORGETDIALOG_H

#include <QDialog>
#include "baseheader.h"
#include "clientsocket.h"

namespace Ui {
class forgetDialog;
}

class forgetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit forgetDialog(Chat_Client &client, QWidget *parent = 0);
    ~forgetDialog();

private slots:
    void on_confrimBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::forgetDialog *ui;
    Chat_Client &mChatClient;
    bool inputEmail;
    QString ans,Uuid;
};

#endif // FORGETDIALOG_H
