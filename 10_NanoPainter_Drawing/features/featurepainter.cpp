#include "featurepainter.h"
#include "featureitem.h"
#include "qnanoboxgradient.h"
#include "QDebug"
featurePainter::featurePainter()
{
    m_patternImage = QNanoImage(":/features/images/pattern1.png", QNanoImage::REPEATX | QNanoImage::REPEATY);
    m_patternImage2 = QNanoImage(":/features/images/pattern2.png", QNanoImage::REPEATX | QNanoImage::REPEATY);
    m_patternImage3 = QNanoImage(":/features/images/pattern3.png", QNanoImage::REPEATX | QNanoImage::REPEATY);
    m_testImage = QNanoImage(":/features/images/quit_logo2.png");
}

void featurePainter::synchronize(QNanoQuickItem *item)
{
    featureItem* realItem = static_cast<featureItem*>(item);
    if(realItem){
        m_viewIndex = realItem->galleryView();
        m_animationSine = realItem->animationSine();
        m_animationTime = realItem->animationTime();

        //qDebug() << m_viewIndex;
    }
}

void featurePainter::drawRect(float x, float y, float w, float h)
{
    painter()->beginPath();
    painter()->rect(x,y,w,h);
    painter()->setLineWidth(w*0.05f);
    painter()->fill();
    painter()->stroke();
}

void featurePainter::drawRectsWithSameColor()
{
    int rects = 7;
    float margin = width()* 0.02f;
    float w = width()/(rects + 1) - margin;
    float posX = w/2 + margin;
    float posY = w/2;
    for(int i = 0 ; i < rects; i++)
    {
        if(i == 0){
            QColor qc1(0,0,0,255);
            QColor qc2(204,102,51,102);
            painter()->setStrokeStyle(QNanoColor::fromQColor(qc1));
            painter()->setFillStyle(QNanoColor::fromQColor(qc2));
            drawRect(posX, posY, w, w);
            posX += w + margin;
            continue;
        }
        painter()->setStrokeStyle(QNanoColor(0,0,0));
        painter()->setFillStyle(QNanoColor(204,102,51,102));
        drawRect(posX, posY, w, w);
        posX += w + margin;
    }
}

void featurePainter::drawRectsWithMix()
{
    int rects = 3;
    float margin = width()*0.02f;
    float w = width() / (rects+2) - margin;
    float posX = w+margin;
    float posY = w+margin;

    QNanoColor c1 = QNanoColor::fromMix(QNanoColor(255,0,0,255), QNanoColor(0,0,0,255),m_animationSine);
    QNanoColor c2 = QNanoColor::fromMix(QNanoColor(255,0,0,100), QNanoColor(0,0,0,0),m_animationSine);
    painter()->setStrokeStyle(c1);
    painter()->setFillStyle(c2);
    drawRect(posX, posY, w,w);

    posX += w + margin;
    QNanoColor c12 = QNanoColor::fromMix(QNanoColor(0,255,0,255), QNanoColor(0,0,0,255), m_animationSine);
    QNanoColor c22 = QNanoColor::fromMix(QNanoColor(0,255,0,100), QNanoColor(0,0,0,0), m_animationSine);
    painter()->setStrokeStyle(c12);
    painter()->setFillStyle(c22);
    drawRect(posX, posY, w,w);

    posX += w + margin;
    QNanoColor c23 = QNanoColor::fromMix(QNanoColor(0,0,255,255), QNanoColor(0,0,255,0), m_animationSine);
    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(c23);
    drawRect(posX, posY, w,w);


}

void featurePainter::drawRectsWithLinearGradient()
{
    int rects = 3;
    float margin = width()* 0.02f;
    float w = width()/(rects+2) - margin;
    float posX = w + margin;
    float posY = 2*(w+margin);

    painter()->setStrokeStyle(QNanoColor(255,255,255));
    QRectF rect1(posX, posY, w, w);
    painter()->setFillStyle(QNanoLinearGradient(0, rect1.y(), 0, rect1.y()+rect1.height()));
    painter()->fillRect(rect1);

    posX += w + margin;
    QNanoLinearGradient g1(0,0,0,0, QNanoColor(0,255,0,255), QNanoColor(255,0,0,255));
    g1.setStartPosition(posX + (w*0.4f*m_animationSine), 0);
    g1.setEndPosition(posX + w - (w*0.4f*m_animationSine), 0);
    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(g1);
    painter()->fillRect(posX, posY, w,w);

    posX += w+margin;
    QRectF rect2(posX, 2*(w+margin), w,w);
    QNanoLinearGradient g2(rect2.x(), rect2.y(), rect2.x() + rect2.width(), rect2.y() + rect2.height());
    g2.setStartColor(QNanoColor(m_animationSine*255, 255, 255));
    g2.setEndColor(QNanoColor(255,m_animationSine*255, 255, 255-m_animationSine*255));
    painter()->setFillStyle(g2);
    painter()->fillRect(rect2);

}

void featurePainter::drawRectsWithRadialGradient()
{
    int rects = 3;
    float margin = width()*0.02f;
    float w = width() / (rects+2) - margin;
    float posX = w + margin;
    float posY = 3*(w+margin);

    QRectF rect1(posX,posY,w,w);
    painter()->setFillStyle(QNanoRadialGradient(rect1.x(), rect1.y(), rect1.width()));
    painter()->fillRect(rect1);
    posX += w + margin;

    QRectF rect2(posX,posY,w,w);
    QNanoRadialGradient g1;
    g1.setStartColor(QNanoColor(0,255,0,255));
    g1.setEndColor(QNanoColor(255,0,0,255));
    g1.setCenterPosition(rect2.x() + rect2.width()/2, rect2.y() + rect2.height()/2);
    g1.setOuterRadius(0.5*w);
    g1.setInnerRadius(0.4*w*m_animationSine);

    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(g1);
    painter()->fillRect(rect2);
    posX += w + margin;

    QRectF rect3(posX,3*(w+margin),w,w);
    QNanoRadialGradient g3(rect3.x() + rect3.width()/2, rect3.y() + rect3.height()/2, w/2, w/4);
    g3.setStartColor(QNanoColor(m_animationSine*255, 255, 255));
    g3.setEndColor(QNanoColor(255, m_animationSine*255, 255, 255-m_animationSine*255));
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void featurePainter::drawRectsWithBoxGradient()
{
    int rects = 3;
    float margin = width()*0.02f;
    float w = width() / (rects+2) - margin;
    float posX = w + margin;
    float posY = 4*(w+margin);

    QRectF rect1(posX,posY,w,w);
    painter()->setFillStyle(QNanoBoxGradient(rect1, w/2));
    painter()->fillRect(rect1);
    posX += w + margin;

    QRectF rect2(posX,posY,w,w);
    QNanoBoxGradient g1;
    g1.setStartColor(QNanoColor(0,255,0,255));
    g1.setEndColor(QNanoColor(255,0,0,255));
    g1.setRect(rect2);
    g1.setRadius(w/8);
    g1.setFeather(w/2 - m_animationSine*w/3);

    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(g1);
    painter()->fillRect(rect2);
    posX += w + margin;

    QRectF rect3(posX,posY,w,w);
    QNanoBoxGradient g3(rect3, w/4, w/8);
    g3.setStartColor(QNanoColor(m_animationSine*255, 255, 255));
    g3.setEndColor(QNanoColor(255, m_animationSine*255, 255, 255-m_animationSine*255));
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void featurePainter::drawRectsWithImagePattern()
{
    int rects = 3;
    float margin = width() * 0.02f;
    float w = width() / (rects + 2) - margin;
    float posX = w + margin;
    float posY = 5*(w+margin);

    QRectF rect1(posX, posY, w, w);
    painter()->setFillStyle(QNanoImagePattern(m_patternImage2));
    painter()->fillRect(rect1);

    posX += w + margin;
    QRectF rect2(posX, posY, w, w);
    QNanoImagePattern g1;
    g1.setImage(m_patternImage);
    g1.setStartPosition(rect2.x() + w/2 , rect2.y() + w/2); // 이미지 중심 기준으로 회전한다.
    //g1.setStartPosition(rect2.x(), rect2.y()); // 이미지 좌측 상단 중심으로 회전한다.
    g1.setImageSize(w/5, w/3);
    g1.setRotation(m_animationTime);
    g1.setAlpha(0.5f + m_animationSine*0.5f);
    painter()->setFillStyle(g1);
    painter()->fillRect(rect2);

    posX += w + margin;
    QRectF rect3(posX, posY, w, w);
    QNanoImagePattern g3(m_patternImage);
    g3.setStartPosition(rect3.x(), rect3.y());
    g3.setImageSize(w*0.1 + m_animationSine*w*0.2f, w*0.15f + m_animationSine*w*0.3f);
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void featurePainter::drawRectsWithBrushStroke()
{
    int rects = 3;
    float margin = width() * 0.02f;
    float border = margin + margin * m_animationSine;
    float w = width() / (rects+2) - margin;
    float w2 = w - border;
    float posX = w + margin + border/2;
    float posY = 6 * (w + margin) + border/2;

//    QRectF rect1(posX, posY, w2, w2);
//    painter()->setLineWidth(border);
//    painter()->setFillStyle(QNanoImagePattern(m_patternImage3));
//    painter()->beginPath();
//    painter()->roundedRect(rect1, border);
//    painter()->fill();

    QRectF rect1(posX, posY, w2, w2);
    painter()->setLineWidth(border);
    painter()->setFillStyle(QNanoImagePattern(m_patternImage3));
    QNanoLinearGradient g1(posX, posY, posX + w2, posY+w2);
    g1.setStartColor("#ffffff");
    g1.setEndColor("#000000");
    painter()->setStrokeStyle(g1);
    painter()->beginPath();
    painter()->roundedRect(rect1, border);
    painter()->fill();
    painter()->stroke();

    posX += w + margin;
    QRectF rect2(posX, posY, w2, w2);
    g1.setStartPosition(posX, posY);
    g1.setEndPosition(posX + w2, posY+w2);
    painter()->setFillStyle(g1);
    painter()->setStrokeStyle(QNanoImagePattern(m_patternImage3));
    painter()->beginPath();
    painter()->roundedRect(rect2, border);
    painter()->fill();
    painter()->stroke();

    posX += w + margin;
    QRectF rect3(posX, posY, w2, w2);
    QNanoRadialGradient g2(posX + w2/4, posY+w2/4, w2);
    g2.setStartColor("#900000ff");
    g2.setEndColor("#90ff0000");
    painter()->setStrokeStyle(g2);
    QNanoImagePattern p1 = QNanoImagePattern(m_patternImage3);
    p1.setImageSize(16,16);
    p1.setStartPosition(m_animationTime*40, 0);
    painter()->setFillStyle(p1);
    painter()->beginPath();
    painter()->roundedRect(rect3, border);
    painter()->fill();
    painter()->stroke();
}

void featurePainter::drawPaths()
{
    int rects = 3;
    float margin = width() * 0.1;
    float w = width() / (rects) - margin;
    float posX = margin/2;
    float posY = margin;
    float lineWidth = width()*0.02f;

    painter()->setFillStyle(0xFFE0E0E0);
    painter()->setStrokeStyle(0xFFE00000);
    painter()->setLineWidth(lineWidth);
    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    painter()->setLineJoin(QNanoPainter::JOIN_ROUND);
    painter()->beginPath();

    ///////////////////////////////////////////////////
    painter()->rect(posX, posY, w, w);

    posX += w + margin;
    painter()->roundedRect(posX, posY, w, w, w/2*m_animationSine);

    posX += w + margin;
    painter()->roundedRect(posX, posY, w, w, w/2*m_animationSine,
                           0, w/2*(cos(m_animationTime)*0.5+0.5), w/4*(sin(m_animationTime*10) * 0.5 + 0.5));
    ///////////////////////////////////////////////////
    posY += w+margin;
    posX = margin/2;
    painter()->ellipse(posX + w/2, posY+w/2, w/3+w/4*m_animationSine, w/3+w/4*(1-m_animationSine));

    posX += w + margin;
    painter()->moveTo(posX+w/2, posY+w/2);
    painter()->arc(posX+w/2, posY+w/2, w/2, 0,0.5f + m_animationSine*5);
    painter()->closePath();

    posX += w + margin;
    QRectF r(posX, posY, w, w);
    painter()->ellipse(r);
    float a = w * 0.1f * m_animationSine;
    float a2 = w*0.1f*(1-m_animationSine);
    r.adjust(w*0.1f+a, w*0.1f+a2, -w*0.1f-a, -w*0.1f-a2);
    painter()->beginHoleSubPath();
    painter()->ellipse(r);
    r.adjust(w*0.2f, w*0.2f, -w*0.2f, -w*0.2f);
    painter()->beginSolidSubPath();
    painter()->rect(r);
    ///////////////////////////////////////////////////
    painter()->stroke();
    painter()->fill();

    ///////////////////////////////////////////////////
    posY += w+margin;
    posX = margin/2;
    painter()->beginPath();
    painter()->moveTo(posX, posY);
    painter()->bezierTo(posX+w*0.2f*m_animationSine, posY+w*0.8f*m_animationSine, posX+w*0.8f*m_animationSine, posY+w*0.2f*m_animationSine, posX+w, posY+w);

    posX += w + margin;
    painter()->moveTo(posX, posY);
    painter()->quadTo(posX+w*0.8f*m_animationSine, posY+w*0.2f*m_animationSine, posX+w, posY+w);

    posX += w + margin;
    painter()->moveTo(posX, posY);
    painter()->arcTo(posX, posY+w, posX+w, posY+w, w*m_animationSine);
    ///////////////////////////////////////////////////

    painter()->stroke();
    ///////////////////////////////////////////////////
    posY += w+margin;
    posX = margin/2;
    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    painter()->setLineJoin(QNanoPainter::JOIN_ROUND);
    painter()->beginPath();
    painter()->moveTo(posX, posY);
    painter()->lineTo(posX, posY+w);
    painter()->lineTo(posX+w, posY+w);
    painter()->lineTo(posX+w*m_animationSine, posY);
    painter()->stroke();

    posX += w+margin;
    painter()->setLineCap(QNanoPainter::CAP_BUTT);
    painter()->setLineJoin(QNanoPainter::JOIN_MITER);
    painter()->beginPath();
    painter()->moveTo(posX, posY);
    painter()->lineTo(posX, posY+w);
    painter()->lineTo(posX+w*m_animationSine, posY);
    painter()->stroke();

    posX += w + margin;
    painter()->setLineCap(QNanoPainter::CAP_SQUARE);
    painter()->setLineJoin(QNanoPainter::JOIN_BEVEL);
    painter()->beginPath();
    painter()->moveTo(posX, posY);
    painter()->lineTo(posX, posY+w);
    painter()->lineTo(posX+w*m_animationSine, posY);
    painter()->stroke();
}

void featurePainter::drawTransforms()
{
    int rects = 3;
    float margin = width()*0.1f;
    float w = width() / (rects) - margin;
    float posX = margin/2;
    float posY = margin;
    float lineWidth = width()*0.01f;

    //////////////////////////////////////////////////////
    painter()->setLineWidth(lineWidth);
    painter()->fillRect(posX, posY, w,w);
    painter()->strokeRect(posX, posY, w, w);
    painter()->save();

    posX += w + margin;
    painter()->setFillStyle(0xFF900000);
    painter()->setStrokeStyle(0xFFE00000);
    painter()->setLineWidth(lineWidth*2);
    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    painter()->setLineJoin(QNanoPainter::JOIN_ROUND);
    painter()->translate(posX + w/2, posY+w/2); // 회전 중심점을 가운데로 옮긴다.
    painter()->rotate(m_animationSine);
    painter()->scale(0.5f + 0.5f*m_animationSine);
    painter()->translate(-(posX + w/2), -(posY + w/2));// 회전 중심점을 복원한다.
    painter()->fillRect(posX, posY, w, w);
    painter()->strokeRect(posX, posY, w, w);

    posX += w+margin;
    painter()->restore(); // restore하지 않으면 그려지는 것도 직전 painter에도 영향이 있다.
    painter()->fillRect(posX, posY, w, w);
    painter()->strokeRect(posX, posY, w, w);
    //////////////////////////////////////////////////////

    posY += w+margin;
    posX = margin/2;
    painter()->setStrokeStyle(0xFF40E040);
    painter()->save();
    painter()->translate(w/8*m_animationSine, w/4*m_animationSine);
    painter()->strokeRect(posX, posY, w/2, w/2);

    posX += w + margin;
    // 기존의 translate가 여전히 유효하기 때문에, 아래의 translate(..)에
    // 더 영향을 받는다. 즉, 2배 크게 움직인다.
    painter()->translate(w/8*m_animationSine, w/4*m_animationSine);
    painter()->strokeRect(posX, posY, w/2, w/2);

    posX += w+margin;
    // 마찬가지로, 기존 translate가 유효하므로, 누적되어 3배 크게 움직인다.
    painter()->translate(w/8 * m_animationSine, w/4 * m_animationSine);
    painter()->strokeRect(posX, posY, w/2, w/2);
    painter()->restore();
    //////////////////////////////////////////////////////

    posY += w+margin;
    posX = margin/2;
    painter()->save();
    painter()->translate(posX + w/2, posY+w/2);
    painter()->skewX(0.4f*m_animationSine);
    painter()->translate(-(posX+w/2), -(posY +w/2));
    painter()->strokeRect(posX, posY, w, w);
    painter()->restore();

    posX += w+margin;
    painter()->save();
    painter()->translate(posX + w/2, posY+w/2);
    painter()->skewY(0.4f*m_animationSine);
    painter()->translate(-(posX+w/2), -(posY +w/2));
    painter()->strokeRect(posX, posY, w, w);
    painter()->restore();

    posX += w + margin;
    QTransform t;
    t.translate(posX + w/2 , posY+w/2);
    t.rotate(m_animationTime*20);
    float scale = 0.5f + 0.5f*m_animationSine;
    t.scale(scale, scale);
    t.translate(-(posX+w/2), -(posY+w/2));
    painter()->transform(t);
    painter()->strokeRect(posX, posY, w, w);

    // 그 다음 transform이 적용될 영역을 지정하여 제한한다.
    painter()->setClipRect(posX, posY, w, w);
    QTransform t2 = painter()->currentTransform();
    // 적용된 transform에 동일한 transform을 누적하게 된다.
    painter()->transform(t2);
    painter()->setStrokeStyle(0xFF40E0E0);
    painter()->strokeRect(posX, posY, w, w);
    painter()->resetClipping();

    posY += w+margin;
    posX = margin/2;
    painter()->resetTransform();
    painter()->setLineWidth(lineWidth);
    QRectF r(posX, posY, w*2, w);
    painter()->strokeRect(r);
    r.adjust(lineWidth/2, lineWidth/2, -lineWidth/2, -lineWidth/2);
    // 그다음 Painter에 적용할 제한 영역을 둔다.
    painter()->setClipRect(r);
    painter()->beginPath();
    painter()->circle(posX+m_animationSine*w*2, posY + w/2, w/2);
    painter()->fill();
    painter()->resetClipping();
}

void featurePainter::drawAntialiasing()
{
    int rects = 3;
    float margin = width() * 0.1f;
    float w = width() / (rects) - margin;
    float posX = margin/2;
    float posY = margin;
    float lineWidth = width()*0.01f;

    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    painter()->setStrokeStyle(0xFFFFFFFF);
    painter()->setLineWidth(lineWidth);
    painter()->setAntialias(0);
    painter()->beginPath();
    painter()->roundedRect(posX, posY, w, w, w/4);
    painter()->stroke();

    posX += w + margin;
    painter()->setAntialias(1.0f);
    painter()->beginPath();
    painter()->roundedRect(posX, posY, w, w, w/4);
    painter()->stroke();

    posX += w + margin;
    painter()->setAntialias(m_animationSine*5);
    painter()->beginPath();
    painter()->roundedRect(posX, posY, w, w, w/4);
    painter()->stroke();

    posY += w + margin;
    posX = margin/2;
    int lines = 12;
    painter()->setAntialias(0);
    painter()->setPixelAlign(QNanoPainter::PIXEL_ALIGN_HALF);
    for(int i =0; i < lines; i ++)
    {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY + i*w/lines);
        painter()->stroke();
    }

    posX += w + margin;
    painter()->setAntialias(1.0f);
    for (int i=0 ; i<lines ; i++) {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY+i*w/lines);
        painter()->stroke();
    }

    posX += w + margin;
    painter()->setAntialias(1.0f + m_animationSine*5);
    for (int i=0 ; i<lines ; i++) {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY+i*w/lines);
        painter()->stroke();
    }

    posY += w + margin;
    posX = margin/2;
    painter()->setAntialias(0);
    for(int i = 0; i < lines; i++){
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY + i*w/lines+5);
        painter()->stroke();
    }

    posX += w + margin;
    painter()->setAntialias(1);
    for(int i = 0; i < lines; i++){
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY + i*w/lines+5);
        painter()->stroke();
    }

    posX += w + margin;
    painter()->setAntialias(1.0f + m_animationSine*5);
    for (int i=0 ; i<lines ; i++) {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY+i*w/lines+5);
        painter()->stroke();
    }

    posX = margin/2;
    posY += w+margin;
    posY += m_animationSine*30;
    painter()->setAntialias(0);
    painter()->setPixelAlign(QNanoPainter::PIXEL_ALIGN_NONE);
    for(int i =0; i < lines; i++)
    {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX + w, posY+i*w/lines +5);
        painter()->stroke();
    }

    posX += w+margin;
    painter()->setAntialias(1.0f);
    for(int i = 0; i < lines; i++)
    {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY+i*w/lines+5);
        painter()->stroke();
    }

    posX += w + margin;
    painter()->setAntialias(1.0f + m_animationSine*5);
    for (int i=0 ; i<lines ; i++) {
        painter()->beginPath();
        painter()->setLineWidth(i*0.5f);
        painter()->moveTo(posX, posY+i*w/lines);
        painter()->lineTo(posX+w, posY+i*w/lines+5);
        painter()->stroke();
    }
}

void featurePainter::drawTextsFonts()
{
    float margin = height() * 0.04f;
    float posX = margin/2;
    float posY = margin;
    painter()->fillText("This is text without setting any font", posX, posY);

    posY += margin;
    QNanoFont f;
    painter()->setFont(f);
    painter()->fillText("This is text with default font", posX, posY);

    posY += margin;
    painter()->setPixelAlignText(QNanoPainter::PIXEL_ALIGN_FULL);
    painter()->fillText("This is text aligned to pixels", posX, posY);
    painter()->setPixelAlignText(QNanoPainter::PIXEL_ALIGN_NONE);

    posY += 2*margin;
    painter()->setFillStyle(0xFFD06060);
    f.setPixelSize(30);
    painter()->setFont(f);
    painter()->fillText("Size 30px", posX, posY);

    posY += 2*margin;
    f.setPointSize(30);
    painter()->setFont(f);
    painter()->fillText("Size 30pt", posX, posY);

    posY += 2*margin;
    painter()->setFillStyle(0xFFFFFFFF);
    QNanoFont f4 = QNanoFont(QNanoFont::DEFAULT_FONT_THIN);
    f4.setPixelSize(margin);
    painter()->setFont(f4);
    painter()->fillText("DEFUALT_FONT_THIN", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_THIN_ITALIC);
    painter()->setFont(f4);
    painter()->fillText("DEFUALT_FONT_THIN_ITALIC", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_LIGHT);
    painter()->setFont(f4);
    painter()->fillText("DEFUALT_FONT_THIN_LIGHT", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_LIGHT_ITALIC);
    painter()->setFont(f4);
    painter()->fillText("DEFAULT_FONT_LIGHT_ITALIC", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_NORMAL);
    painter()->setFont(f4);
    painter()->fillText("DEFAULT_FONT_NORMAL", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_NORMAL_ITALIC);
    painter()->setFont(f4);
    painter()->fillText("DEFAULT_FONT_NORMAL_ITALIC", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_BOLD);
    painter()->setFont(f4);
    painter()->fillText("DEFAULT_FONT_BOLD", posX, posY);

    posY += margin;
    f4.setFontId(QNanoFont::DEFAULT_FONT_BOLD_ITALIC);
    painter()->setFont(f4);
    painter()->fillText("DEFAULT_FONT_BOLD_ITALIC", posX, posY);

    posY += 2*margin;
    QNanoFont f2 = QNanoFont(":/features/fonts/Pacifico.ttf");
    f2.setPixelSize(margin*2);
    painter()->setFont(f2);
    painter()->fillText("This is text with custom font", posX, posY);

    posY += 2*margin;
    f2.setBlur(margin*0.2f + margin*0.4f*m_animationSine);
    painter()->setFont(f2);
    painter()->fillText("This is text with some glowing", posX, posY);
    f2.setBlur(0);
    painter()->setFont(f2);
    painter()->setFillStyle(0xFF000000);
    painter()->fillText("This is text with some glowing", posX, posY);

    posY += 2*margin;
    QNanoFont f5 = QNanoFont();
    f5.setPixelSize(margin*0.8f);
    f5.setLetterSpacing(6*m_animationSine-2);
    painter()->setFont(f5);
    painter()->setFillStyle(0xFFFFFFFF);
    painter()->fillText("This is text with varing letter spacing", posX, posY);
}

void featurePainter::drawTextsAlignments()
{
    float margin = height() * 0.2f;
    float fontSize = height() * 0.04f;
    float posX = margin/2;
    float posY = margin/2;

    QNanoFont f3;
    f3.setPixelSize(fontSize);
    painter()->setFont(f3);

    ////////////////////////////////////////////////////
    posX = width() * 0.5f;
    painter()->setFillStyle(0xFF808080);
    painter()->fillRect(posX-1, posY-fontSize,2,fontSize*3);
    painter()->setTextBaseline(QNanoPainter::BASELINE_BOTTOM);

    painter()->setFillStyle(0xFFFF9090);
    painter()->setTextAlign(QNanoPainter::ALIGN_LEFT);
    painter()->fillText("ALIGN_LEFT", posX, posY);

    painter()->setFillStyle(0xFF90FF90);
    painter()->setTextAlign(QNanoPainter::ALIGN_CENTER);
    painter()->fillText("ALIGN_CENTER", posX, posY+fontSize);

    painter()->setFillStyle(0xFF9090FF);
    painter()->setTextAlign(QNanoPainter::ALIGN_RIGHT);
    painter()->fillText("ALIGN_RIGHT", posX, posY+fontSize*2);
    ////////////////////////////////////////////////////

    posY += margin;
    posX = width() * 0.1f;
    painter()->setFillStyle(0xFF808080);
    painter()->fillRect(width()*0.1f, posY-1, width()*0.8f, 2);

    painter()->setTextAlign(QNanoPainter::ALIGN_LEFT);
    painter()->setFillStyle(0xFFFF9090);
    painter()->setTextBaseline(QNanoPainter::BASELINE_BOTTOM);
    painter()->fillText("BASELINE_BOTTOM", posX, posY);

    painter()->setFillStyle(0xFF90FF90);
    painter()->setTextBaseline(QNanoPainter::BASELINE_ALPHABETIC);
    painter()->fillText("BASELINE_ALPHABETIC", posX+width()*0.4f, posY);

    painter()->setFillStyle(0xFF9090FF);
    painter()->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
    painter()->fillText("BASELINE_MIDDLE", posX + width()*0.2f, posY);

    painter()->setFillStyle(0xFFFF90FF);
    painter()->setTextBaseline(QNanoPainter::BASELINE_TOP);
    painter()->fillText("BASELINE_TOP", posX + width()*0.5f, posY);
    ////////////////////////////////////////////////////

    posY += margin;
    QString s("This is a test string which is slightly longer one. Yes, we want long string for this.");
    painter()->setFillStyle(0xFFFFFFFF);
    painter()->setTextAlign(QNanoPainter::ALIGN_CENTER);
    QRectF rect1(width()*0.1f, posY, width()*0.8f-m_animationSine*width()*0.4f, 100);
    painter()->fillText(s, rect1);
    ////////////////////////////////////////////////////

    posY += margin;
    painter()->setTextAlign(QNanoPainter::ALIGN_RIGHT);
    QRectF bounds = painter()->textBoundingBox(s, width()*0.1f, posY, width()*0.8f-m_animationSine*width()*0.4f);
    painter()->setFillStyle(0x80808080);
    painter()->fillRect(bounds);
    painter()->setFillStyle(0xFFFFFF80);
    painter()->fillText(s, bounds);
}

void featurePainter::drawImages()
{
    float margin = height()*0.05f;
    float posX = width()*0.1f;
    float posY = margin;

    ///////////////////////////////////////////////////
    QRectF rect1(0,0,width(), height());
    painter()->setFillStyle(QNanoImagePattern(m_patternImage2));
    painter()->fillRect(rect1);

    QNanoImage image(":/features/images/quit_logo2.png");
    painter()->drawImage(image, posX, posY);
    ///////////////////////////////////////////////////

    ///////////////////////////////////////////////////
    // 이미지에서 일부분을 떼어난다.
    posY += image.height() + margin;
    QRectF sourceArea(0,100,image.width(), image.height()-100); // 일부분 크기 지정
    // 떼어낸 이미지를 붙일 영역을 지정한다.
    float cx = width()/2;
    float r = width()*0.15f + m_animationSine*width()*0.25f;
    QRectF targetArea(cx-r, posY, r*2, width()*0.1);
    painter()->drawImage(m_testImage, sourceArea, targetArea);
    ///////////////////////////////////////////////////

    // 이미지 회전, 스케일
    posY += targetArea.height() + height() * 0.15f;
    image.setFilename(":/features/images/qnanopainter_small.png");
    QRectF rect(cx-r/2, posY-r/2, r,r);
    QPointF c(rect.x()+ rect.width()/2, rect.y() + rect.height()/2);
    painter()->save();
    painter()->translate(c);
    painter()->rotate(m_animationTime);
    painter()->translate(-c);
    painter()->drawImage(image, rect);
    painter()->restore();
    ///////////////////////////////////////////////////

    posY = height() * 0.6f;
    float posY2 = posY + (height()*0.15f);
    bool useNearest = (m_animationSine > 0.5f);
    QNanoImage imageNoMipmap(":/features/images/qnanopainter_small.png");
    QNanoImage imageNoMipmapNearest(":/features/images/qnanopainter_small.png", QNanoImage::NEAREST);
    QNanoImage imageMipmap(":/features/images/qnanopainter_small.png", QNanoImage::GENERATE_MIPMAPS);
    QNanoImage imageMipmapNearest(":/features/images/qnanopainter_small.png", QNanoImage::GENERATE_MIPMAPS | QNanoImage::NEAREST);

    float sizeDiff = width() * 0.05f;
    float centerY = 4*sizeDiff;
    for(int i = 0; i<5; ++i)
    {
        float size = (i+1) *sizeDiff;
        QRectF rect2(posX, posY+ centerY-size/2, size, size);
        painter()->drawImage(useNearest? imageNoMipmapNearest : imageNoMipmap, rect2);

        QRectF rect3(posX, posY2+centerY-size/2, size, size);
        painter()->drawImage(useNearest ? imageMipmapNearest : imageMipmap, rect3);

        posX += size + 2;
    }
    QNanoFont font(QNanoFont::DEFAULT_FONT_BOLD);
    font.setPixelSize(QNanoPainter::mmToPx(4));
    painter()->setTextAlign(QNanoPainter::ALIGN_CENTER);
    painter()->setTextBaseline(QNanoPainter::BASELINE_TOP);
    QString scaling = useNearest ? "NEAREST" : "LINEAR";
    QString offString = QString("MIPMAPS: OFF, TEXTURE: %1").arg(scaling);
    QString onString = QString("MIPMAPS: ON, TEXTURE: %1").arg(scaling);
    float text1PosY = posY+centerY/2;
    float text2PosY = posY2+centerY/2;
    font.setBlur(margin*0.05);
    painter()->setFont(font);
    painter()->setFillStyle("#000000");
    painter()->fillText(offString, cx, text1PosY);
    painter()->fillText(onString, cx, text2PosY);
    font.setBlur(0);
    painter()->setFillStyle("#ffffff");
    painter()->setFont(font);
    painter()->fillText(offString, cx, text1PosY);
    painter()->fillText(onString, cx, text2PosY);
}

void featurePainter::paint(QNanoPainter *painter)
{
    if(m_viewIndex == 0)
    {
        drawRectsWithSameColor();
        drawRectsWithMix();
        drawRectsWithLinearGradient();
        drawRectsWithRadialGradient();
        drawRectsWithBoxGradient();
        drawRectsWithImagePattern();
        drawRectsWithBrushStroke();
    }
    else if(m_viewIndex ==1)
    {
        drawPaths();
    }
    else if(m_viewIndex == 2)
    {
        drawTransforms();
    }
    else if(m_viewIndex == 3)
    {
        drawAntialiasing();
    }
    else if(m_viewIndex == 4)
    {
        drawTextsFonts();
    }
    else if(m_viewIndex == 5)
    {
        drawTextsAlignments();
    }
    else if(m_viewIndex == 6)
    {
        drawImages();
    }
    else {
        QString szText = QString::number(m_viewIndex);
        painter->fillText(szText, width()/2, height()/2);

        QString szText2 = QString::number(m_animationSine);
        painter->fillText(szText2, width()/2, height()/2+20);

    }
}

