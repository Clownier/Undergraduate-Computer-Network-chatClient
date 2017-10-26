#include<clientsocket.h>



Chat_Client::Chat_Client(){
    if(WSAStartup(W_VERSION_REQUEST,&wD)){
        sprintf(error,"Client initialize winsock error!\tcode: %d\n",WSAGetLastError());
        qDebug()<<error;
    }
    else if(wD.wVersion != W_VERSION_REQUEST){
        qDebug()<<"Client's winsock version error!\n";
        WSACleanup();
    }
    else
        qDebug()<<"Client's winsock initialized !\n";
}

Chat_Client::~Chat_Client(){
    //closesocket(client_Socket);
}

void Chat_Client::create(){
    client_Socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_Socket == INVALID_SOCKET){
        sprintf(error,"Client create socket error!\tcode: %d\n",WSAGetLastError());
        qDebug()<<error;
        WSACleanup();
    }else
        qDebug()<<"Client socket create OK!\n";
}

void Chat_Client::bind(){
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CLIENT_PORT);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (::bind(client_Socket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR) {
        sprintf(error,"Client socket bind error!\tcode: %d\n",WSAGetLastError());
        closesocket(client_Socket);
        WSACleanup();
        qDebug()<<error;
    }else
        qDebug()<<"Client socket bind OK!\n";

}

void Chat_Client::connect() {

    QSettings *configIniWrite = new QSettings("test.ini",QSettings::IniFormat);
    QString QserverIP = configIniWrite->value("ip/serverIP").toString();
    string serverIP = QserverIP.toStdString();
    int serverPort = configIniWrite->value("port/serverPort").toInt();
    delete configIniWrite;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str());
    if (::connect(client_Socket, (LPSOCKADDR)&addr, sizeof(addr))==SOCKET_ERROR) {
        sprintf(error,"Client socket connect error!\tcode: %d\n",WSAGetLastError());
        qDebug()<<error;
        closesocket(client_Socket);
        WSACleanup();
    }else
        qDebug()<<"connect Server success!\n";
}

int Chat_Client::send(string sendBuf) {
    if (::send(client_Socket, sendBuf.c_str(), sendBuf.length() + 1, 0) == SOCKET_ERROR) {
        sprintf(error,"send error!\tcode:%d\n",WSAGetLastError());
        qDebug()<<error;
        return -1;
    }else
        return 1;
}

int Chat_Client::send(){
    qDebug()<<sendBuf;
    return send(sendBuf);
}

string Chat_Client::recv(){
    //char recbuf[BUFLEN + 1];
    memset(recvBuf,'\0',BUFLEN);
    int nRC = ::recv(client_Socket, recvBuf, BUFLEN, 0);
    recvBuf[nRC] = '\0';
    qDebug()<<"recvBuf = "<<recvBuf<<"\n";
    string res(recvBuf);
    return res;
}

void Chat_Client::close(){
    closesocket(client_Socket);
    WSACleanup();
}
