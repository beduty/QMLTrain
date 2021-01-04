#include "helloitem.h"

HelloItem::HelloItem(QQuickItem *parent) : QNanoQuickItem(parent)
{

}

QNanoQuickItemPainter *HelloItem::createItemPainter() const
{
    return new HelloItemPainter();
}

void HelloItemPainter::paintHelloItem(QNanoPainter *p, float width, float height)
{
    float size = std::min(width, height);
    QPointF center(width/2, height/2);
    // Paint the background circle
    QNanoRadialGradient gradient1(center.x(), center.y() - size*0.1, size*0.6);
    gradient1.setStartColor("#909090");
    gradient1.setEndColor("#404040");
    p->beginPath();
    p->circle(center, size*0.46);
    p->setFillStyle(gradient1);
    p->fill();
    p->setStrokeStyle("#202020");
    p->setLineWidth(size*0.01);
    p->stroke();
    // Hello text
    p->setTextAlign(QNanoPainter::ALIGN_CENTER);
    p->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
    QNanoFont font1(QNanoFont::DEFAULT_FONT_BOLD_ITALIC);
    font1.setPixelSize(size*0.09);
    p->setFont(font1);
    p->setFillStyle("#C0E050");
    p->fillText("HELLO", center.x(), center.y() - size*0.18);
    // QNanoPainter text
    QNanoFont font2(QNanoFont::DEFAULT_FONT_THIN);
    font2.setPixelSize(size*0.16);
    p->setFont(font2);
    p->fillText("QNanoPainter", center.x(), center.y() - size*0.08);
    // Paint heart
    QNanoImage logo(":/quitlogo.png",
                    QNanoImage::GENERATE_MIPMAPS |
                    QNanoImage::REPEATX |
                    QNanoImage::REPEATY);
    float patternSize = size*0.02;
    QNanoImagePattern pattern(logo, center.x(), center.y(), patternSize, patternSize);
    p->setFillStyle(pattern);
    p->setLineCap(QNanoPainter::CAP_ROUND);
    p->setStrokeStyle("#B0D040");
    p->beginPath();
    p->moveTo(center.x(), center.y() + size*0.3);
    p->bezierTo(center.x() - size*0.25, center.y() + size*0.1,
                center.x() - size*0.05, center.y() + size*0.05,
                center.x(), center.y() + size*0.15);
    p->bezierTo(center.x() + size*0.05, center.y() + size*0.05,
                center.x() + size*0.25, center.y() + size*0.1,
                center.x(), center.y() + size*0.3);
    p->stroke();
    p->fill();
}

void HelloItemPainter::paint(QNanoPainter *painter)
{
    paintHelloItem(painter, width(), height());
}
