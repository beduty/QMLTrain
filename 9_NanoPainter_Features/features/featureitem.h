#ifndef FEATUREITEM_H
#define FEATUREITEM_H

#include <QObject>
#include "qnanoquickitem.h"
#include "featurepainter.h"
#include "qnanoimage.h"
class featureItem : public QNanoQuickItem
{
    Q_OBJECT
    QNANO_PROPERTY(int, m_galleryView, galleryView, setGalleryView)
    Q_PROPERTY(float animationSine READ animationSine WRITE setAnimationSine NOTIFY animationSineChanged)
    Q_PROPERTY(float animationTime READ animationTime WRITE setAnimationTime NOTIFY animationTimeChange)
    float m_animationSine;
    float m_animationTime;

public:
    explicit featureItem(QQuickItem *parent = nullptr);
    QNanoQuickItemPainter *createItemPainter() const;
    float animationSine() const;
    float animationTime() const;

public slots:
    void setAnimationSine(float animationSine);
    void setAnimationTime(float animationTime);

signals:
    void animationSineChanged(float animationSine);
    void animationTimeChange(float animationTime);
};

#endif // FEATUREITEM_H
