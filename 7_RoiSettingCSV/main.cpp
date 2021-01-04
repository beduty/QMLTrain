#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "roiinfofile.h"
#include "roiitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<CRoiInfoFile>("CRoiInfoFile",1,0,"CRoiInfoFile");
    qmlRegisterType<RoiItem>("RoiItem",1,0,"RoiItem");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
