#include <QCursor>
#include "meitem.h"
#include "mepainter.h"
meItem::meItem(QQuickItem *parent) : QNanoQuickItem(parent)
{
    m_circleSize = 10;
    m_resizableItem = -1;
    m_hoveringItem = -1;
    m_resizing = false;
}

QNanoQuickItemPainter *meItem::createItemPainter() const
{
    return new mePainter();
    //return new EventItemPainter();
}

void meItem::genRandomItems()
{
    m_items.clear();
    int margin = int(width() * 0.05);

    int items = 2+ qrand()%50;
    for (int i = 0; i< items; i++)
    {
        double w = qrand() % int(width() * 0.2) + margin;
        double h = qrand() % int(height() * 0.2) + margin;
        double x = qrand() % int(width() - margin*2 - w) + margin;
        double y = qrand() % int(height() - margin*2 - h) + margin;
        //m_items<<QRectF(x,y,w,h);
        m_items.push_back(QRectF(x,y,w,h));
    }
    update();
}

void meItem::hoverMoveEvent(QHoverEvent *event)
{
    int resizeItem = resizeItemAt(event->pos());
    if(resizeItem != m_resizableItem)
    {
        m_resizableItem = resizeItem;
        update();
    }

    int hoverItem = topItemAt(event->pos());
    if(hoverItem != m_hoveringItem)
    {
        m_hoveringItem = hoverItem;
        update();
    }

    if(m_resizableItem != -1){
        m_hoveringItem = -1;
    }

    if(m_resizableItem != -1){
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }else if(m_hoveringItem != -1){
        setCursor(QCursor(Qt::OpenHandCursor));
    }else {
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void meItem::mousePressEvent(QMouseEvent *event)
{
    int resizeItem = resizeItemAt(event->pos());
    if(resizeItem != -1)
    {
        m_resizing = true;
        m_resizableItem = resizeItem;
        m_pressedItem = resizeItem;
        update();
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else{
        int pressItem = topItemAt(event->pos());
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
}

void meItem::mouseMoveEvent(QMouseEvent *event)
{
    if(m_resizableItem != -1)
    {
        QRectF *item = &m_items[m_resizableItem];
        if(m_resizing){
            item->setBottomRight(event->pos());
        }
    }
    else{
        if(m_pressedItem != -1)
        {
            QRectF *item = &m_items[m_pressedItem];
            item->moveTo(event->pos()-m_pressPos);
        }
    }
    update();
}

void meItem::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_resizableItem = m_pressedItem = -1;
    update();
}


void meItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if(widthValid() && heightValid())
    {
        m_circleSize = 2 + int(qMin(width(),height()) * 0.01);
        genRandomItems();
    }
}

int meItem::topItemAt(QPointF pos)
{
    for(int i = m_items.count()-1; i>=0; i--)
    {
        if(m_items.at(i).contains(pos))
        {
            return i;
        }
    }
    return -1;
}

int meItem::resizeItemAt(QPointF pos)
{
    for(int i = m_items.count()-1; i>=0; i--)
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
















