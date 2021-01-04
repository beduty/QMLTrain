#include "eventitem.h"
#include <QtDebug>
#include <QCursor>

EventItem::EventItem(QQuickItem *parent) : QNanoQuickItem(parent)
{
    m_circleSize = 10;
    m_activeItem = -1;
    m_pressedItem = -1;
    m_resizableItem = -1;
    m_resizing = false;
    m_hovered = false;
}

QNanoQuickItemPainter *EventItem::createItemPainter() const
{
    return new EventItemPainter();
}

#define QRAND() qrand()
void EventItem::generateRandomItems()
{
    m_items.clear();
    int margin = int(width()*0.05);
    int items = 2+QRAND()%150;
    for(int i =0; i < items; i++){
        double w = QRAND() % int(width()*0.2)+margin;
        double h = QRAND() % int(height()*0.2)+margin;
        double x = QRAND() % int(width()-w-margin*2) + margin;
        double y = QRAND() % int(height()-h-margin*2) + margin;
        m_items<<QRectF(x,y,w,h);
    }
    update();
}

int EventItem::topItemAt(QPointF pos)
{
    for(int i = m_items.count()-1; i>=0; i--)
    {
        if(m_items.at(i).contains(pos)){
            return i;
        }
    }
    return -1;
}

int EventItem::resizeItemAt(QPointF pos)
{
    for(int i = m_items.count()-1; i>= 0; i--)
    {
        QRectF item = m_items.at(i);
        QPointF p = item.bottomRight() - pos;
        if(p.manhattanLength() <= m_circleSize*2)
            return i;
        else if(item.contains(pos)){
            break;
        }
    }
    return -1;
}

void EventItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    // 윈도우 창 크기 변경될 때.
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if(widthValid() && heightValid()){
        m_circleSize = 2 + int(qMin(width(), height())*0.01);
        generateRandomItems();
    }
}

void EventItem::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "LOG: mousePressEvent";
    int resizeItem = resizeItemAt(event->pos());
    if(resizeItem != -1)
    {
        m_resizing = true;
        //m_resizableItem = resizeItem;
        m_pressedItem = resizeItem;
        update();
        setCursor(QCursor(Qt::SizeFDiagCursor));
        qDebug() << "resizeItem : "<<resizeItem;
        //int topIndex = m_items.count()-1;

    }



//    int resizeItem = resizeItemAt(event->pos());
//    if(resizeItem != -1)
//    {
//        int topIndex = m_items.count()-1;
//        m_items.move(resizeItem, topIndex);
//        update();
//        setCursor(QCursor(Qt::SizeFDiagCursor));
//    }

    int pressItem = topItemAt(event->pos());
    qDebug() << pressItem;
    if(pressItem != -1){
        m_pressedItem = pressItem;
        m_pressPos = event->pos() - m_items[pressItem].topLeft();
        update();
        setCursor(QCursor(Qt::OpenHandCursor));
    }
    if(m_pressedItem == -1)
    {
        event->setAccepted(false);
    }

}

void EventItem::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressedItem != -1)
    {
        QRectF *item = &m_items[m_pressedItem];
        if(m_resizing){
            item->setBottomRight(event->pos());
        }
        else {
            item->moveTo(event->pos()-m_pressPos);
        }
    }
    update();

}

void EventItem::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "LOG : mouseReleaseEvent";
    Q_UNUSED(event);
    if(!mouseHoverEventsEnabled()){
        m_activeItem = -1;
    }
    m_pressedItem = -1;
    m_resizing = false;
    setCursor(QCursor(Qt::ArrowCursor));
    update();
}

void EventItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    int item = topItemAt(event->pos());
    m_items.removeAt(item);
    m_activeItem = m_resizableItem = m_pressedItem = -1;
    update();
}

void EventItem::hoverEnterEvent(QHoverEvent *event)
{
    qDebug() << "hoverEnterEvent";
    Q_UNUSED(event);
    m_hovered = true;
    update();
}

void EventItem::hoverMoveEvent(QHoverEvent *event)
{
    qDebug() << "hoverMoveEvent";
    int resizeItem = resizeItemAt(event->pos());
    if(resizeItem != m_resizableItem)
    {
        m_resizableItem = resizeItem;
        update();
    }

    int hoverItem = topItemAt(event->pos());
    if(hoverItem != m_activeItem){
        m_activeItem = hoverItem;
        update();
    }

    if(m_resizableItem != -1){
        m_activeItem = -1;
    }

    if(m_resizableItem != -1){
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }else if(m_activeItem != -1){
        setCursor(QCursor(Qt::OpenHandCursor));
    }else{
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void EventItem::hoverLeaveEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;
    update();
}

////////////////////////////////////////////////////////////////////

EventItemPainter::EventItemPainter()
{
    m_circleSize = 10;
    m_pressedItem = -1;
    m_activeItem = -1;
    m_resizableItem = -1;
    m_hovered = false;
    m_resizing = false;
}

void EventItemPainter::paint(QNanoPainter *painter)
{
    painter->setGlobalAlpha(m_hovered?1.0:0.5);
    painter->beginPath();
    painter->setFillStyle(0xFF408070);
    painter->setStrokeStyle(0xFFD0D0D0);
    painter->rect(0,0,width(),height());
    painter->setLineWidth(2);
    painter->fill();
    painter->stroke();

    painter->setLineWidth(1);
    for(int i =0; i<m_items.count(); i++)
    {
        QRectF box = m_items.at(i);
        bool isActive= (m_activeItem == i);
        bool isPressed = (m_pressedItem == i);
        QNanoColor fillColor(isPressed ? 0xFFFF0000 : isActive ? 0xFFFFFFFF : 0xFF000000);
        fillColor.setAlphaF(0.2f);

        // 사각형 테두리
        painter->setFillStyle(fillColor);
        painter->setStrokeStyle(0xFFD0D0D0);
        painter->beginPath();
        painter->rect(box);
        painter->fill();
        painter->stroke();

        // 코너 원
        painter->beginPath();
        bool isResizable = (m_resizableItem == i);
        painter->setFillStyle(isResizable ? 0x80F0F0F0 : 0x00F0F0F0);
        painter->circle(box.x()+box.width(), box.y()+box.height(), m_circleSize);
        painter->stroke();
        painter->fill();

        // ITem 번호
        painter->setFillStyle(0xFFE0E0E0);
        painter->setTextAlign(QNanoPainter::ALIGN_CENTER);
        painter->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
        QNanoFont font(QNanoFont::DEFAULT_FONT_BOLD);
        font.setPointSize(12);
        painter->setFont(font);
        painter->fillText(QString::number(i+1), box.center());
    }
}

void EventItemPainter::synchronize(QNanoQuickItem *item)
{
    EventItem *realItem = static_cast<EventItem*>(item);
    if(realItem){
        m_items = realItem->m_items;
        m_circleSize = realItem->m_circleSize;
        m_pressedItem = realItem->m_pressedItem;
        m_resizableItem = realItem->m_resizableItem;
        m_activeItem = realItem->m_activeItem;
        m_hovered = realItem->m_hovered;
    }
}














