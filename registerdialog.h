#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "clientsocket.h"

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(Chat_Client &client, QWidget *parent = 0);
    ~registerDialog();

private slots:
    void on_registerBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::registerDialog *ui;
    QString regEmail,regNikeName,regPassword,
        regRePassword,regSecReq,regSecAns;
    Chat_Client &mChatClient;
};

#endif // REGISTERDIALOG_H
