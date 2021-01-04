#include "featureitem.h"
#include "featurepainter.h"
FeatureItem::FeatureItem(QQuickItem *parent) : QNanoQuickItem(parent)
{
    setHighQualityRendering(true);
}

QNanoQuickItemPainter *FeatureItem::createItemPainter() const
{
    return new FeaturePainter();
}

float FeatureItem::animationSine() const
{
    return m_animationSine;
}

float FeatureItem::animationTime() const
{
    return m_animationTime;
}

void FeatureItem::setAnimationSine(float animationSine)
{
    //qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_animationSine, animationSine))
        return;

    m_animationSine = animationSine;
    emit animationSineChanged(m_animationSine);
    update();
}

void FeatureItem::setAnimationTime(float animationTime)
{
    //qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_animationTime, animationTime))
        return;

    m_animationTime = animationTime;
    emit animationTimeChanged(m_animationTime);
    update();
}
