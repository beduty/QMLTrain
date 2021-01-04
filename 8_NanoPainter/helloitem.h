#ifndef HELLOITEM_H
#define HELLOITEM_H

#include <QObject>
#include "qnanoquickitem.h"
#include "qnanoquickitempainter.h"


class HelloItemPainter : public QNanoQuickItemPainter
{
public:
    HelloItemPainter(){}
    void paintHelloItem(QNanoPainter *p, float width, float height);
protected:
    void paint(QNanoPainter *painter);
};

class HelloItem : public QNanoQuickItem
{
    Q_OBJECT
public:
    explicit HelloItem(QQuickItem *parent = nullptr);

signals:
    // QNanoQuickItem interface
protected:
    QNanoQuickItemPainter *createItemPainter() const;
};

#endif // HELLOITEM_H
