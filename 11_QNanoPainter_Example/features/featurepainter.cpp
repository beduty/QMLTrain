#include "featurepainter.h"
#include "featureitem.h"
#include "qnanoradialgradient.h"
#include "qnanoboxgradient.h"
FeaturePainter::FeaturePainter() : m_viewIndex(0)
{
    m_testImage = QNanoImage(":/features/images/quit_logo2.png");
    m_patternImage = QNanoImage(":/features/images/pattern1.png", QNanoImage::REPEATX | QNanoImage::REPEATY);
    m_patternImage2 = QNanoImage(":/features/images/pattern2.png", QNanoImage::REPEATX | QNanoImage::REPEATY);
    m_patternImage3 = QNanoImage(":/features/images/pattern3.png", QNanoImage::REPEATX | QNanoImage::REPEATY);
}

void FeaturePainter::paint(QNanoPainter *painter)
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
    else if(m_viewIndex ==1){
        drawPaths();
    }
    else if(m_viewIndex ==2){
        drawTransforms();
    }
    else if(m_viewIndex ==3){
        drawAntialiasing();
    }
    else
    {
        QString szViewIdx = QString::number(m_viewIndex);
        painter->fillText(szViewIdx, width()/2, height()/2 - 20);

        QString szAnimSine = QString::number(m_animationSine);
        painter->fillText(szAnimSine, width()/2, height()/2);

        QString szAnimTime = QString::number(m_animationTime);
        painter->fillText(szAnimTime, width()/2, height()/2 + 20);
    }
}

void FeaturePainter::synchronize(QNanoQuickItem *item)
{
    auto realItem = static_cast<FeatureItem*>(item);
    if(realItem)
    {
        m_viewIndex = realItem->galleryView();
        m_animationSine = realItem->animationSine();
        m_animationTime = realItem->animationTime();
    }
}

void FeaturePainter::drawRect(float x, float y, float w, float h)
{
    painter()->beginPath();
    painter()->rect(x,y,w,h);
    painter()->setLineWidth(w*0.05f);
    painter()->fill();
    painter()->stroke();
}

void FeaturePainter::drawRectsWithSameColor()
{
    int rects = 6;
    float margin = width() * 0.02f;
    float w = width() / (rects+1) - margin;
    float posX = w/2 + margin;
    float posY = w/2 - margin;

    painter()->setStrokeStyle(QNanoColor(0,0,0));
    painter()->setFillStyle(QNanoColor(204,102,51,102));
    drawRect(posX, posY, w, w);

    posX += w + margin;
    painter()->setStrokeStyle("#000000");
    painter()->setFillStyle(0x66CC6633);
    drawRect(posX, posY, w, w);

    posX += w + margin;
    QNanoColor c1;
    QNanoColor c2;
    c2.setRed(204);
    c2.setGreen(102);
    c2.setBlue(51);
    c2.setAlpha(102);
    painter()->setStrokeStyle(c1);
    painter()->setFillStyle(c2);
    drawRect(posX, posY, w, w);

    posX += w + margin;
    QNanoColor cf1;
    QNanoColor cf2;
    cf2.setRedF(0.8f);
    cf2.setGreenF(0.4f);
    cf2.setBlueF(0.2f);
    cf2.setAlphaF(0.4f);
    painter()->setStrokeStyle(cf1);
    painter()->setFillStyle(cf2);
    drawRect(posX, posY, w, w);

    posX += w + margin;
    QColor qc1(0,0,0,255);
    QColor qc2(204,102,51, 102);
    painter()->setStrokeStyle(QNanoColor::fromQColor(qc1));
    painter()->setFillStyle(QNanoColor::fromQColor(qc2));
    drawRect(posX, posY, w, w);

    posX += w + margin;
    QNanoColor cc1(c1);
    QNanoColor cc2(c2);
    painter()->setStrokeStyle(cc1);
    painter()->setFillStyle(cc2);
    drawRect(posX, posY, w,w);
}

void FeaturePainter::drawRectsWithMix()
{
    int rects = 3;
    float margin = width() * 0.02f;
    float w = width() / (rects + 2) - margin;
    float posX = w + margin;
    float posY = w + margin;

    // 시작 색상 ~ 끝 색상 사이의 값을 리턴한다. (m_animationSine 0~1사이의 값을 넣으면,
    // m_animationSize값에 해당하는 색상값을 리턴한다.)
    QNanoColor c1 = QNanoColor::fromMix(
                        QNanoColor(255,0,0,255),
                        QNanoColor(0,0,0,255),
                        m_animationSine
                    );
    QNanoColor c2 = QNanoColor::fromMix(
                        QNanoColor(255,0,0,100),
                        QNanoColor(0,0,0,0),
                        m_animationSine
                    );
    painter()->setStrokeStyle(c1);
    painter()->setFillStyle(c2);
    drawRect(posX, posY, w,w);

    posX += w + margin;
    QNanoColor c12 = QNanoColor::fromMix(
                        QNanoColor(0,255,0,255),
                        QNanoColor(0,0,0,255),
                        m_animationSine
                    );
    QNanoColor c22 = QNanoColor::fromMix(
                        QNanoColor(0,255,0,100),
                        QNanoColor(0,0,0,0),
                        m_animationSine
                    );
    painter()->setStrokeStyle(c12);
    painter()->setFillStyle(c22);
    drawRect(posX, posY, w,w);

    posX += w + margin;
    QNanoColor c23 = QNanoColor::fromMix(QNanoColor(0,0,255,255), QNanoColor(0,0,255,0), m_animationSine);
    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(c23);
    drawRect(posX,posY,w,w);
}

void FeaturePainter::drawRectsWithLinearGradient()
{
    int rects = 3;
    float margin = width() * 0.02f;
    float w = width() / (rects + 2) - margin;
    float posX = w + margin;
    float posY = 2*(w+margin);

    QNanoLinearGradient g1;
    g1.setStartPosition(posX + (w*0.4f*m_animationSine),0);
    g1.setEndPosition(posX + w - (w*0.4f*m_animationSine),0);
    g1.setStartColor(QNanoColor(0,255,0,255));
    g1.setEndColor(QNanoColor(255,0,0,255));
    painter()->setFillStyle(g1);
    painter()->fillRect(posX,posY,w,w);


    posX += w + margin;
    QRectF rect2(posX,posY,w,w);
    QNanoLinearGradient g2;
    g2.setStartPosition(0, posY + (w*0.4f*m_animationSine));
    g2.setEndPosition(0, posY + w - (w*0.4f*m_animationSine));
    g2.setStartColor(QNanoColor(0,255,0,255));
    g2.setEndColor(QNanoColor(255,0,0,255));
    painter()->setFillStyle(g2);
    painter()->fillRect(rect2);
    posX += w + margin;

    QRectF rect3(posX,posY,w,w);
    QNanoLinearGradient g3;
    g3.setStartPosition(posX + (w*0.4f*m_animationSine)
                        , posY + (w*0.4f*m_animationSine));
    g3.setEndPosition(posX + w - (w*0.4f*m_animationSine)
                      , posY + w - (w*0.4f*m_animationSine));
    g3.setStartColor(QNanoColor(0,255,0,255));
    g3.setEndColor(QNanoColor(255,0,0,255));
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void FeaturePainter::drawRectsWithRadialGradient()
{
    int rects = 3;
    float margin = width() * 0.02f;
    float w = width()/(rects+2) - margin;
    float posX = w + margin;
    float posY = 3*(w+margin);

    QRectF rect1(posX, posY, w, w);
    painter()->setFillStyle(QNanoRadialGradient(rect1.x(), rect1.y(), rect1.width()));
    painter()->fillRect(rect1);

    posX += w+margin;
    QRectF rect2(posX, posY, w, w);
    QNanoRadialGradient g2;
    g2.setStartColor(QNanoColor(0,255,0,255));
    g2.setEndColor(QNanoColor(255,0,0,255));
    g2.setCenterPosition(rect2.x() + rect2.width()/2
                         , rect2.y() + rect2.height()/2);
    g2.setOuterRadius(0.5*w);
    g2.setInnerRadius(0.4*w*m_animationSine);
    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(g2);
    painter()->fillRect(rect2);

    posX += w+margin;
    QRectF rect3(posX, 3*(w+margin), w, w);
    //QNanoRadialGradient g3(rect3.x() + rect3.width()/2, rect3.y() + rect3.height()/2, w/2, w/4);
    QNanoRadialGradient g3;
    g3.setCenterPosition(rect3.x() + rect3.width()/2, rect3.y()+rect3.height()/2);
    g3.setOuterRadius(w/2);
    g3.setInnerRadius(w/4);
    g3.setStartColor(QNanoColor(m_animationSine*255,255,255));
    g3.setEndColor(QNanoColor(255, m_animationSine*255, 255, 255-m_animationSine*255));
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void FeaturePainter::drawRectsWithBoxGradient()
{
    int rects = 3;
    float margin = width() * 0.02f;
    float w = width() / (rects +2) - margin;
    float posX = w + margin;
    float posY = 4*(w+margin);

    QRectF rect1(posX, posY, w, w);
    painter()->setFillStyle(QNanoBoxGradient(rect1, w/2));
    painter()->fillRect(rect1);

    posX += w + margin;
    QRectF rect2(posX, posY, w, w);
    QNanoBoxGradient g2;
    g2.setStartColor(QNanoColor(0,255,0,255));
    g2.setEndColor(QNanoColor(255,0,0,255));
    g2.setRect(rect2);
    g2.setRadius(w/8);
    g2.setFeather(w/2 - m_animationSine*w/3);
    painter()->setStrokeStyle(QNanoColor(255,255,255));
    painter()->setFillStyle(g2);
    painter()->fillRect(rect2);

    posX += w+margin;
    QRectF rect3(posX, posY, w, w);
    //QNanoBoxGradient g3(rect3,w/4, w/8);
    QNanoBoxGradient g3;
    g3.setRect(rect3);
    g3.setFeather(w/4);
    g3.setRadius(w/8);
    g3.setStartColor(QNanoColor(m_animationSine*255, 255, 255));
    g3.setEndColor(QNanoColor(255, m_animationSine*255, 255, 255-m_animationSine*255));
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void FeaturePainter::drawRectsWithImagePattern()
{
    int rects = 3;
    float margin = width()*0.02f;
    float w = width()/(rects+2)-margin;
    float posX = w + margin;
    float posY = 5*(w+margin);

    QRectF rect1(posX, posY, w, w);
    painter()->setFillStyle(QNanoImagePattern(m_patternImage2));
    painter()->fillRect(rect1);

    posX += w+margin;
    QRectF rect2(posX, posY, w, w);
    QNanoImagePattern g2;
    g2.setImage(m_patternImage);
    g2.setImageSize(w/5, w/3);

    // 회전 중심점 역할을 한다.
    //g2.setStartPosition(rect2.x() + w/2, rect2.y()+w/2);
    //g2.setStartPosition(rect2.x(), rect2.y());
    g2.setStartPosition(rect2.x()+rect2.width(), rect2.y()+rect2.height());

    g2.setRotation(m_animationTime);
    g2.setAlpha(0.5f + m_animationSine*0.5f);
    painter()->setFillStyle(g2);
    painter()->fillRect(rect2);

    posX += w + margin;
    QRectF rect3(posX, posY, w,w);
    QNanoImagePattern g3;
    g3.setImage(m_patternImage);
    //g3.setStartPosition(rect3.x(), rect3.y());
    g3.setStartPosition(rect3.x()+rect3.width()/2 , rect3.y()+rect3.height()/2);
    g3.setImageSize(w*0.1 + m_animationSine*w*0.2f, w*0.15f+m_animationSine*w*0.3f);
    painter()->setFillStyle(g3);
    painter()->fillRect(rect3);
}

void FeaturePainter::drawRectsWithBrushStroke()
{
    int rects = 3;
    float margin = width()*0.02f;
    float border = margin*(1+m_animationSine);
    float w = width()/(rects+2) - margin;
    float w2 = w - border;
    float posX = w + margin + border/2;
    float posY = 6*(w+margin) + border/2;

    //////////////////////////////////////////////////
    QRectF rect1(posX, posY, w2, w2);
    painter()->beginPath();
    painter()->setFillStyle(QNanoImagePattern(m_patternImage3));
    painter()->roundedRect(rect1, border);
    painter()->fill();

    QNanoLinearGradient g1;
    g1.setStartPosition(posX, posY);
    g1.setEndPosition(posX + w2, posY + w2);
    g1.setStartColor("#ffffff");
    g1.setEndColor("#000000");
    painter()->setLineWidth(border);
    painter()->setStrokeStyle(g1);
    painter()->stroke();
    //////////////////////////////////////////////////

    posX += w + margin;
    QRectF rect2(posX,posY,w2,w2);

    painter()->beginPath();

    g1.setStartPosition(posX, posY);
    g1.setEndPosition(posX + w2, posY + w2);
    painter()->setFillStyle(g1);
    painter()->roundedRect(rect2, border);
    painter()->fill();

    painter()->setStrokeStyle(QNanoImagePattern(m_patternImage3));
    painter()->stroke();
    //////////////////////////////////////////////////
    posX += w +margin;

    QRectF rect3(posX, posY, w2, w2);
    painter()->beginPath();
    QNanoImagePattern p3 = QNanoImagePattern(m_patternImage3);
    p3.setImageSize(16,16);
    p3.setStartPosition(m_animationTime*40,0);
    painter()->setFillStyle(p3);
    painter()->roundedRect(rect3, border);
    painter()->fill();

    QNanoRadialGradient g3;
    g3.setCenterPosition(posX + w2/4, posY+w2/4);
    g3.setOuterRadius(w2);
    g3.setInnerRadius(0.0f);
    g3.setStartColor("#900000ff");
    g3.setEndColor("#90ff0000");
    painter()->setStrokeStyle(g3);
    painter()->stroke();
    //////////////////////////////////////////////////
}

void FeaturePainter::drawPaths()
{
    int rects = 3;
    float margin = width()*0.1f;
    float w = width()/(rects) - margin;
    float posX = margin/2;
    float posY = margin;
    //float lineWidth = width()*0.02f;
    float lineWidth = margin/4;//width()*0.02f;

    painter()->setFillStyle(0xFFE0E0E0);
    painter()->setStrokeStyle(0xFFE00000);
    painter()->setLineWidth(lineWidth);
    // Line의 끝 부분 둥그렇게 한다.
    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    // Line과 Line의 연결부분을 동그랗게 한다.
    painter()->setLineJoin(QNanoPainter::JOIN_ROUND);

    painter()->beginPath();
    painter()->setLineWidth(margin/4);
    painter()->moveTo(posX, posY);
    painter()->lineTo(posX+w, posY);
    painter()->lineTo(posX+w, posY+w);
    painter()->lineTo(posX, posY);

    posX += w + margin;
    painter()->roundedRect(posX, posY, w, w, w/2*m_animationSine);

    posX += w + margin;
    // 시계방향 꼭지점 Radius적용(TopLeft(TL)->TR->BR->BL)
    painter()->roundedRect(posX, posY, w, w,
                           w/2*m_animationSine,
                           0,
                           w/2*(cos(m_animationSine)*0.5 + 0.5),
                           w/4*(sin(m_animationTime*10) * 0.5 + 0.5));
//    painter()->fill();
//    painter()->stroke();


    posY += w+margin;
    posX = margin/2;
    painter()->ellipse(posX + w/2, posY+w/2, w/3+w/4*m_animationSine, w/3+w/4*(1-m_animationSine));

    posX += w+ margin;
    painter()->moveTo(posX +w/2, posY + w/2);
    painter()->arc(posX + w/2, posY + w/2, w/2,
                   0, // 시작각도(rad)
                   0.5f + m_animationSine*5); // 종료각도 (rad)
    painter()->closePath();

    // Hole SubPath는 잘 모르겠다.
    posX += w +margin;
    QRectF r(posX, posY, w, w);
    painter()->ellipse(r);
    float a = w * 0.1f * m_animationSine;
    float a2 = w * 0.1f*(1- m_animationSine);
    r.adjust(w*0.1f+a, w*0.1f+a2, -w*0.1f-a, -w*0.1f-a2);
    painter()->beginHoleSubPath();
    painter()->ellipse(r); // ellipse만큼의 Hole이 뚫린다.
    r.adjust(w*0.2f, w*0.2f, -w*0.2f, -w*0.2f);
    painter()->beginSolidSubPath();
    painter()->rect(r);

    painter()->fill();
    painter()->stroke();

    // painter()->fill() 또는 stroke()하고 나면 다시 beginPath()를 해줘야 한다.
    posY += w + margin;
    posX = margin/2;
    painter()->beginPath();
    painter()->moveTo(posX, posY);
    painter()->bezierTo(posX+w*0.2f*m_animationSine, posY+w*0.8f*m_animationSine, posX + w*0.8f*m_animationSine, posY+w*0.2f*m_animationSine, posX+w, posY +w);

    posX += w + margin;
    painter()->moveTo(posX, posY);
    painter()->quadTo(posX + w* 0.8f*m_animationSine, posY + w*0.2f*m_animationSine, posX + w, posY + w);

    posX += w + margin;
    painter()->moveTo(posX, posY);
    painter()->arcTo(posX, posY+w, posX + w, posY+w, w*m_animationSine);

    painter()->stroke();

    ///////////////////////////
    posY += w+margin;
    posX = margin/2;
    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    painter()->setLineJoin(QNanoPainter::JOIN_ROUND);
    painter()->beginPath();
    painter()->moveTo(posX, posY);
    painter()->lineTo(posX, posY+w);
    painter()->lineTo(posX+w*m_animationSine, posY);
    painter()->stroke();

    posX += w + margin;
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

void FeaturePainter::drawTransforms()
{
    int rects = 3;
    float margin = width()*0.1f;
    float w = width()/(rects) - margin;
    float posX = margin/2;
    float posY = margin;
    float lineWidth = width() * 0.03f;

    painter()->setLineWidth(lineWidth);
    painter()->fillRect(posX, posY, w, w);
    painter()->strokeRect(posX, posY, w, w);
    painter()->save();

    posX += w + margin;
    painter()->setFillStyle(0xFF900000);
    painter()->setStrokeStyle(0xFFE00000);
    painter()->setLineWidth(lineWidth*2);
    painter()->setLineCap(QNanoPainter::CAP_ROUND);
    painter()->setLineJoin(QNanoPainter::JOIN_ROUND);
    painter()->translate(posX + w/2, posY + w/2);
    painter()->rotate(m_animationSine);
    painter()->scale(0.5f + 0.5f*m_animationSine);
    painter()->translate(-(posX+w/2),-(posY+w/2));
    painter()->fillRect(posX, posY, w, w);
    painter()->strokeRect(posX, posY, w,w);

    posX += w+margin;
    painter()->restore();
    painter()->fillRect(posX, posY, w, w);
    painter()->strokeRect(posX, posY, w, w);

    posY += w+margin;
    posX = margin/2;
    painter()->setStrokeStyle(0xFF40E040);
    painter()->save();
    painter()->translate(w/8*m_animationSine, w/4*m_animationSine);
    painter()->strokeRect(posX, posY, w/2, w/2);
    // painter()->restore();

    // painter()->save();
    posX += w + margin;
    painter()->translate(w/8*m_animationSine, w/4*m_animationSine);
    painter()->strokeRect(posX, posY, w/2, w/2);
    // painter()->restore();

    // painter()->save();
    posX += w + margin;
    painter()->translate(w/8*m_animationSine, w/4*m_animationSine);
    painter()->strokeRect(posX, posY, w/2, w/2);
    painter()->restore();


    posY += w+margin;
    posX = margin/2;
    painter()->save();
    painter()->translate(posX+w/2, posY+w/2);
    painter()->skewX(0.4f * m_animationSine);
    painter()->translate(-(posX+w/2), -(posY+w/2));
    painter()->strokeRect(posX, posY, w,w);
    painter()->restore();

    posX += w+margin;
    painter()->save();
    painter()->translate(posX+w/2, posY+w/2);
    painter()->skewY(0.4f * m_animationSine);
    painter()->translate(-(posX+w/2), -(posY+w/2));
    painter()->strokeRect(posX, posY, w, w);
    painter()->restore();

    posX += w + margin;
    QTransform t;
    t.translate(posX + w/2, posY + w/2);
    t.rotate(m_animationTime*20);
    float scale = 0.5f*(1+m_animationSine);
    t.scale(scale, scale);
    t.translate(-(posX+w/2), -(posY+w/2));
    painter()->transform(t);
    painter()->strokeRect(posX, posY, w, w);
    painter()->setClipRect(posX, posY, w, w);

    QTransform t2 = painter()->currentTransform();
    painter()->transform(t2);
    painter()->setStrokeStyle(0xFF40E0E0);
    painter()->strokeRect(posX, posY, w, w);
    painter()->resetClipping();


    posY += w + margin;
    posX = margin/2;
    painter()->resetTransform();
    painter()->setLineWidth(lineWidth);

    QRectF r(posX, posY, w*2, w);
    painter()->strokeRect(r);
    r.adjust(lineWidth/2, lineWidth/2, -lineWidth/2, -lineWidth/2);
    painter()->setClipRect(r);
    painter()->beginPath();
    painter()->circle(posX + m_animationSine*w*2, posY+w/2, w/2);
    painter()->fill();
    painter()->resetClipping();
}

void FeaturePainter::drawAntialiasing()
{

}









































