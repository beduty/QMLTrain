#ifndef CLOCKCIRCLE_H
#define CLOCKCIRCLE_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QTime>
#include <QTimer>
#include <QPainter>

class ClockCircle : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor borderActiveColor READ borderActiveColor WRITE setBorderActiveColor NOTIFY borderActiveColorChanged)
    Q_PROPERTY(QColor borderNonActiveColor READ borderNonActiveColor WRITE setBorderNonActiveColor NOTIFY borderNonActiveColorChanged)
    Q_PROPERTY(qreal angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(QTime circleTime READ circleTime WRITE setCircleTime NOTIFY circleTimeChanged)

public:
    explicit ClockCircle(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);

    Q_INVOKABLE void clear();
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QString name() const;
    QColor backgroundColor() const;
    QColor borderActiveColor() const;
    QColor borderNonActiveColor() const;
    qreal angle() const;
    QTime circleTime() const;

public slots:
    void setName(QString name);
    void setBackgroundColor(QColor backgroundColor);
    void setBorderActiveColor(QColor borderActiveColor);
    void setBorderNonActiveColor(QColor borderNonActiveColor);
    void setAngle(qreal angle);
    void setCircleTime(QTime circleTime);

signals:
    void cleared();

    void nameChanged(QString name);
    void backgroundColorChanged(QColor backgroundColor);
    void borderActiveColorChanged(QColor borderActiveColor);
    void borderNonActiveColorChanged(QColor borderNonActiveColor);
    void angleChanged(qreal angle);
    void circleTimeChanged(QTime circleTime);

private:
    QString m_name;
    QColor m_backgroundColor;
    QColor m_borderActiveColor;
    QColor m_borderNonActiveColor;
    qreal m_angle;
    QTime m_circleTime;

    QTimer *internalTimer;
};

#endif // CLOCKCIRCLE_H
