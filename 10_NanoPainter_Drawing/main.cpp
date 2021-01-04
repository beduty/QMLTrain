#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mouseEvents/meitem.h"
#include "features/featureitem.h"
#include "drawings/drawingitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<meItem>("MouseEventItem", 1,0,"MouseEventItem");
    qmlRegisterType<featureItem>("FeaturesItem", 1,0,"FeaturesItem");
    qmlRegisterType<DrawingItem>("DrawingItem", 1, 0, "DrawingItem");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
