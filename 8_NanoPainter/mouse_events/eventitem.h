#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <QObject>
#include "qnanoquickitem.h"
#include "qnanoquickitempainter.h"

class EventItem : public QNanoQuickItem
{
    Q_OBJECT
public:
    explicit EventItem(QQuickItem *parent = nullptr);
    QNanoQuickItemPainter *createItemPainter() const;

public Q_SLOTS:
    void generateRandomItems();
protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void hoverEnterEvent(QHoverEvent *event);
    void hoverMoveEvent(QHoverEvent *event);
    void hoverLeaveEvent(QHoverEvent *event);

private:
    friend class EventItemPainter;
    int topItemAt(QPointF pos);
    int resizeItemAt(QPointF pos);
    QList<QRectF> m_items;
    bool m_resizing;
    bool m_hovered;
    int m_circleSize;
    int m_pressedItem;
    int m_resizableItem;
    int m_activeItem;
    QPointF m_pressPos;
};


class EventItemPainter : public QNanoQuickItemPainter
{
public:
    EventItemPainter();
    void paint(QNanoPainter *painter);
    void synchronize(QNanoQuickItem *item);

private:
    QList<QRectF> m_items;
    bool m_resizing;
    bool m_hovered;
    int m_circleSize;
    int m_activeItem;
    int m_pressedItem;
    int m_resizableItem;
};

#endif // EVENTITEM_H
