#ifndef MEPAINTER_H
#define MEPAINTER_H

#include <QObject>
#include "qnanoquickitempainter.h"

class mePainter : public QNanoQuickItemPainter
{
public:
    mePainter();
    void paint(QNanoPainter *painter);
    void synchronize(QNanoQuickItem *item);

private:
    QList<QRectF> m_items;
    int m_circleSize;
    int m_hoveringItem;
    int m_resizableItem;

    int m_pressedItem;
    bool m_resizing;
};

#endif // MEPAINTER_H
