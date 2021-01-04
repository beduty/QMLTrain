#ifndef FEATUREITEM_H
#define FEATUREITEM_H

#include <QQuickItem>
#include "qnanoquickitem.h"
#include "qnanoquickitempainter.h"
#include "featurepainter.h"

class FeatureItem : public QNanoQuickItem
{
    Q_OBJECT
    QNANO_PROPERTY(int, m_galleryView, galleryView, setGalleryView)
    Q_PROPERTY(float animationSine READ animationSine WRITE setAnimationSine NOTIFY animationSineChanged)
    Q_PROPERTY(float animationTime READ animationTime WRITE setAnimationTime NOTIFY animationTimeChanged)

public:
    FeatureItem(QQuickItem* parent = nullptr);
    QNanoQuickItemPainter *createItemPainter() const;
    float animationSine() const;
    float animationTime() const;

public slots:
    void setAnimationSine(float animationSine);
    void setAnimationTime(float animationTime);

signals:
    void animationSineChanged(float animationSine);
    void animationTimeChanged(float animationTime);

private:
    float m_animationSine;
    float m_animationTime;
};

#endif // FEATUREITEM_H
