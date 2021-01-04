#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "helloitem.h"
#include "mouse_events/eventitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<HelloItem>("HelloItem", 1,0, "HelloItem");
    qmlRegisterType<EventItem>("EventItem",1,0,"EventItem");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
