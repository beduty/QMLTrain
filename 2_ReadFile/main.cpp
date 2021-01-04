#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "fileio.h"
#include <QSettings>
#include <QFile>
#include<QDebug>
#include "rcpinfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<FileIO, 1>("FileIO", 1,0, "FileIO");
    qmlRegisterType<RcpInfo, 1>("RcpInfo", 1,0, "RcpInfo");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
