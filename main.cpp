#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    MainWindow w;
    w.show();

    return a.exec();
}
