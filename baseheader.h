#ifndef BASEHEADER_H
#define BASEHEADER_H

#include<winsock2.h>
#include<iostream>
#include<cstdio>
#include <windows.h>
#include <process.h>
#include <winbase.h>
#include <QDebug>
#include<map>
#include<string>
#include<QSettings>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonParseError>
#include<QMessageBox>
#include<QListWidget>
#include<QTimer>

#define BUFLEN 255
//#define SERVER_PORT  5050
#define BUFLEN  255
#define CLIENT_PORT  0
#define COMMENT_CHAR '#'
using namespace std;
//const string SERVER_IP = "10.10.95.171";
const WORD W_VERSION_REQUEST = 0x0101;

#endif // BASEHEADER_H
