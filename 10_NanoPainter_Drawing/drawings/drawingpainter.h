#ifndef DRAWINGPAINTER_H
#define DRAWINGPAINTER_H
#include "qnanoquickitem.h"
#include "qnanoquickitempainter.h"
#include <QQueue>
#include <QVector>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

class Path : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    Path() : m_opacity(1) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "opacity");
        animation->setDuration(2000);
        animation->setStartValue(1);
        animation->setEndValue(0);
        m_hideAnimation.addPause(3000);
        m_hideAnimation.addAnimation(animation);
    };
    ~Path(){};
    float opacity() const
    {
        return m_opacity;
    }
    void setOpacity(float opacity){
        m_opacity = opacity;
        emit opacityChanged(m_opacity);
    }

signals:
    void opacityChanged(float opacity);

private:
    friend class DrawingPainter;
    float m_opacity;
    QVector<QPoint> m_points;
    QSequentialAnimationGroup m_hideAnimation;
};


class DrawingPainter : public QObject, public QNanoQuickItemPainter
{
    // DrawingPainter에서 connect signal-slot을 사용하기 위해서는
    // QObject를 상속받아서 Q_OBJECT 매크로를 사용한다.
    Q_OBJECT
public:
    DrawingPainter();

signals:
    void update();

protected:
    void paint(QNanoPainter *painter);
    void synchronize(QNanoQuickItem *item);

private:
    void drawPathLine(const QVector<QPoint> &points, const QPoint translate);
    QQueue<QSharedPointer<Path>> m_paths;
};

#endif // DRAWINGPAINTER_H
