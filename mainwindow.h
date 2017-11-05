#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsocket.h"
#include "serversocket.h"

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

private:
    Ui::MainWindow *ui;
    QListWidget *userList;
    void initListWidget();
    void listenOther();
    void recv();
    QString recvInfo();
    QString MyName;
    QString MyUuid;
    QString aimUserUuid;
    bool aimUserOnline;
    std::thread otherThread;
    bool first =true;
};

#endif // MAINWINDOW_H
