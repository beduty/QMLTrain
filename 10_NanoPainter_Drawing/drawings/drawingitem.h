#ifndef DRAWINGITEM_H
#define DRAWINGITEM_H

#include "qnanoquickitem.h"
#include <QVector>

class QNanoQuickItemPainter;

class DrawingItem : public QNanoQuickItem
{
    Q_OBJECT
public:
    explicit DrawingItem(QQuickItem *parent = nullptr);
    QNanoQuickItemPainter *createItemPainter() const;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    friend class DrawingPainter;
    QVector<QPoint> m_points;
    int m_pointsSynced;
};

#endif // DRAWINGITEM_H
