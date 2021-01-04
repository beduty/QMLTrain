#include "featureitem.h"
#include "QDebug"
featureItem::featureItem(QQuickItem *parent) : QNanoQuickItem(parent)
{
    setHighQualityRendering(true);
}

QNanoQuickItemPainter *featureItem::createItemPainter() const
{
    return new featurePainter();
}

float featureItem::animationSine() const
{
    return m_animationSine;
}

float featureItem::animationTime() const
{
    return m_animationTime;
}

void featureItem::setAnimationSine(float animationSine)
{
    //qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_animationSine, animationSine))
        return;
    m_animationSine = animationSine;
    emit animationSineChanged(m_animationSine);
    update();
}

void featureItem::setAnimationTime(float animationTime)
{
    //qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_animationTime, animationTime))
        return;

    m_animationTime = animationTime;
    emit animationTimeChange(m_animationTime);
    update();
}
