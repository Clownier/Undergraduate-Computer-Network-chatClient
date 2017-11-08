#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsocket.h"
#include "serversocket.h"
#include"baseheader.h"
#include"senderwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Chat_Client mChatClient,aimSocket;

signals:
    void getData(QString);

private slots:
    void on_userListWidget_currentTextChanged(const QString &currentText);
    void showOtherText(QString);
    void on_sendText_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QListWidget *userList;
    void initListWidget();
    void listenOther();
    void recv();
    void showOfflineMes();
    QString recvInfo();
    QString MyName;
    QString MyUuid;
    QString aimUserUuid;
    bool aimUserOnline;
    std::thread otherThread;
    bool first =true;
    std::vector<QString> offlineMes;
    QString aimIp;
    int aimPort;
};

#endif // MAINWINDOW_H
