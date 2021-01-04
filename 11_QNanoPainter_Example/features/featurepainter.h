#ifndef FEATUREPAINTER_H
#define FEATUREPAINTER_H

#include "qnanoquickitem.h"
#include "qnanoquickitempainter.h"

class FeaturePainter : public QNanoQuickItemPainter
{
public:
    FeaturePainter();
protected:
    void paint(QNanoPainter *painter);
    void synchronize(QNanoQuickItem *item);

private:
    void drawRect(float x, float y, float w, float h);
    void drawRectsWithSameColor();
    void drawRectsWithMix();
    void drawRectsWithLinearGradient();
    void drawRectsWithRadialGradient();
    void drawRectsWithBoxGradient();
    void drawRectsWithImagePattern();
    void drawRectsWithBrushStroke();

private:
    void drawPaths();
    void drawTransforms();
    void drawAntialiasing();

private:
    int m_viewIndex;
    float m_animationSine;
    float m_animationTime;
    QNanoImage m_testImage;
    QNanoImage m_patternImage;
    QNanoImage m_patternImage2;
    QNanoImage m_patternImage3;
};

#endif // FEATUREPAINTER_H
