#include "mepainter.h"
#include "QDebug"
#include "QtMath"
#include "meitem.h"
mePainter::mePainter()
{
    m_circleSize = 10;
    m_hoveringItem = -1;
    m_resizableItem = -1;
    m_pressedItem = -1;
    m_resizing = false;
}

void mePainter::paint(QNanoPainter *painter)
{
    painter->setGlobalAlpha(1.0);
    painter->beginPath();
    painter->setFillStyle(0xFF408070);
    painter->rect(0,0,width(),height());
    painter->fill();
    painter->setStrokeStyle(0xFFD0D0D0);
    painter->setLineWidth(2);
    painter->stroke();

    painter->setLineWidth(1);
    for(int i = 0; i < m_items.count(); i++)
    {
        QRectF box = m_items.at(i);
        bool bHovering = (m_hoveringItem == i);
        bool bPressed = (m_pressedItem ==i) ;
        QNanoColor fillColor(bPressed ? 0xFFFF0000 : bHovering ? 0xFFFFFFFF : 0xFF000000);
        fillColor.setAlphaF(0.2f);

        painter->setFillStyle(fillColor);
        painter->beginPath();
        painter->rect(box);
        painter->fill();
        painter->setStrokeStyle(0xFFD0D0D0);
        painter->stroke();

        painter->setFillStyle(0xFFE0E0E0);
        painter->setTextAlign(QNanoPainter::ALIGN_CENTER);
        painter->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
        QNanoFont font(QNanoFont::DEFAULT_FONT_BOLD);
        font.setPointSize(12);
        painter->setFont(font);
        painter->fillText(QString::number(i+1), box.center());

        painter->beginPath();
        painter->circle(box.x() + box.width(), box.y()+box.height(), m_circleSize);
        painter->stroke();
        painter->setFillStyle((m_resizableItem != i)? 0x00F0F0F0:0x80F0F0F0);
        painter->fill();
    }
}

void mePainter::synchronize(QNanoQuickItem *item)
{
    meItem *Item = static_cast<meItem*>(item);
    if(Item)
    {
        m_items = Item->m_items;
        m_circleSize = Item->m_circleSize;
        m_hoveringItem = Item->m_hoveringItem;
        m_resizableItem = Item->m_resizableItem;

        m_pressedItem = Item->m_pressedItem;
        m_resizing = Item->m_resizing;
    }
}
