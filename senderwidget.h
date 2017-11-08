#ifndef SenderWidget_H
#define SenderWidget_H

#include <QWidget>
#include<baseheader.h>

struct ProtocalDatagram {
    quint8 isAck=0; //0:file_packages,1:ack
    quint16 index=0;
    quint16 size=0;
    QByteArray data;
};

inline QDataStream &operator <<(QDataStream &out,const ProtocalDatagram & proDatagram) {
    out << proDatagram.isAck << proDatagram.index << proDatagram.size << proDatagram.data;
    return out;
}

inline QDataStream &operator >>(QDataStream &in,ProtocalDatagram & proDatagram) {
    quint8 isAck;
    quint16 index,size;
    QByteArray data;
    in >> isAck >> index >> size >> data;

    proDatagram.isAck = isAck;
    proDatagram.index = index;
    proDatagram.size = size;
    proDatagram.data = data;
    return in;
}


class SendedFile
{
public:
    quint64 fileSize;
    static SendedFile* GetInstance();
    static void Release();
private:
    SendedFile();
    static SendedFile* pInstance;
};




class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
    void sendData(const ProtocalDatagram & proDatagram);
    void sendFile();
    QHostAddress addr;
    quint16 port;
    int MssLen; //单位kb
    int groupNum;
    int windowSize;
    int head,tail;
    void initSocket(quint16 myPort);

signals:
    void sendFileSize(quint64 size);
    void sendFileMaxSize(quint64 size);
    void passProdata(const ProtocalDatagram & prodata);

public slots:
    void getFileName(const QString &fileName);
    void getIpAddress(QHostAddress ipAddr,quint16 port);
    void readPendingDatagrams();
    void timeoutResend();
    void sendToThread(const ProtocalDatagram & prodata);

private:
    QUdpSocket *udpSocket;
    QFile file;
    int lineLen;
    int lineSended;
    quint64 fileSize;
    int threadIndex;
    int NotReceiveNum;
    int multiAck[100000];
    //QHash<quint8,QPair<ProtocalDatagram *,int>> packages;
    //QHash<quint8,SenderThread *> threadpool;
    QQueue<QPair<bool,ProtocalDatagram *>*> ackedRec;
    ProtocalDatagram* readFile();
    QTimer *timer;
    //QVector<SenderThread*> threadpool;
};







namespace Ui {
class SenderWidget;
}

class SenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SenderWidget(QWidget *parent = 0,quint16 aimPort = 0,quint16 myProt = 0,QHostAddress aimIP = QHostAddress("127.0.0.1"));
    ~SenderWidget();
    quint64 filereceived;
    quint64 filePerSec;

private:
    Ui::SenderWidget *ui;
    Sender *udpsender;

signals:
    void setFileName(const QString &fileName);
    void setUdpAddress(QHostAddress Ip,quint16 Port);

private slots:

    void on_fileButton_clicked();
    void on_portButton_clicked();
    void on_MssButton_clicked();
    void updateProgressBar();
    void setProgressBarMax(quint64 size);
};

#endif // SenderWidget_H
