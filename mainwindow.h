#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Chat_Client mChatClient;

private slots:
    void on_userListWidget_currentTextChanged(const QString &currentText);

    void on_sendText_clicked();

private:
    Ui::MainWindow *ui;
    QListWidget *userList;
    void initListWidget();
    QString recvInfo();
    QString MyName;
};

#endif // MAINWINDOW_H
