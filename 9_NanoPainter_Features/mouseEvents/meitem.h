#ifndef MEITEM_H
#define MEITEM_H

#include <QObject>
#include "qnanoquickitem.h"
class meItem : public QNanoQuickItem
{
    Q_OBJECT
public:
    explicit meItem(QQuickItem *parent = nullptr);
    QNanoQuickItemPainter *createItemPainter() const;\

public Q_SLOTS:
    void genRandomItems();

protected:
    void hoverMoveEvent(QHoverEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private:
    int topItemAt(QPointF pos);
    int resizeItemAt(QPointF pos);

private:
    friend class mePainter;
    QList<QRectF> m_items;
    bool m_resizing;
    int m_pressedItem;
    QPointF m_pressPos;

    int m_circleSize;
    int m_hoveringItem;
    int m_resizableItem;
};

#endif // MEITEM_H
