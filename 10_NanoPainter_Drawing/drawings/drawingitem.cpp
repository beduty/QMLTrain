#include "drawingitem.h"
#include "drawingpainter.h"
#include "QtDebug"

DrawingItem::DrawingItem(QQuickItem *parent) : QNanoQuickItem(parent)
  , m_pointsSynced(0)
{
    setHighQualityRendering(true);
}

QNanoQuickItemPainter *DrawingItem::createItemPainter() const
{
    //qDebug() << "createItemPainter"; // 최초 1회 호출
    DrawingPainter *itemPainter = new DrawingPainter();
    QObject::connect(itemPainter, &DrawingPainter::update, this, &DrawingItem::update);
    return itemPainter;
}

void DrawingItem::mousePressEvent(QMouseEvent *event)
{
    // Mouse 클릭할 때, 포인트를 새로 추가한다. QVector::Append
    // Start a new line
    m_pointsSynced = 0;
    m_points.clear();
    m_points.append(event->pos());
    update(); // painter의 DrawingPainter::syncronize()에서 m_points를 처리한다.
}

void DrawingItem::mouseMoveEvent(QMouseEvent *event)
{
    // pressed + mouseMove일 때마다 호출된다.
    // qDebug() << "move";
    m_points.append(event->pos());
    update();
}

void DrawingItem::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // INT_MAX로 Drawing Line이 끝났음을 알린다.
    m_points.append(QPoint(INT_MAX,0));
    update();
}




















