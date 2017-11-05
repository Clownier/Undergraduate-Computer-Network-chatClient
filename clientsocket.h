#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include<baseheader.h>
#include<string>


class  Chat_Client {
public:
    Chat_Client();
    Chat_Client(SOCKET socket,sockaddr_in addr);
    ~Chat_Client();
    void create();
    void bind();
    void connect();
    void connect(QString serverIP,int serverPort);
    //int carry();
    int send(string sendbuf);
    int send();
    void close();
    string recv();
    QString Qrecv();
    int Qsend(QString);
    //全局的临界区保护变量，以保护主线程和子线程都要访问的sendBuf
    //CRITICAL_SECTION gCriticalSection;
    //unsigned __stdcall GetInputs(void *arg);
    char sendBuf[BUFLEN], recvBuf[BUFLEN],error[BUFLEN];
    QString serverIP;
    int serverPort;
    sockaddr_in client_Addr;
    //static QString myUuid;

private:
    //FD_SET rfds, wfds;
    SOCKET client_Socket;
    WSADATA wD;
    QString surplus;
};


#endif // CLIENTSOCKET_H
