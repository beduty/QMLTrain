#include "clockcircle.h"

ClockCircle::ClockCircle(QQuickItem *parent) : QQuickPaintedItem(parent)
  , m_backgroundColor(Qt::white)
  , m_borderActiveColor(Qt::blue)
  , m_borderNonActiveColor(Qt::gray)
  , m_angle(0)
  , m_circleTime(QTime(0,0,0,0))
{

    internalTimer = new QTimer(this);
    connect(internalTimer, &QTimer::timeout, [=](){
        setAngle(angle()-0.3);  // m_angle 값의 증가방향은 왼쪽!! 음수로 감소시켜야 우측으로 움직인다!
        setCircleTime(circleTime().addMSecs(50));
        update(); // paint()가 호출된다.
    });
}

void ClockCircle::paint(QPainter *painter)
{
    QBrush brush(m_backgroundColor);
    QBrush brushActive(m_borderActiveColor);
    QBrush brushNonActive(m_borderNonActiveColor);

    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setBrush(brushNonActive);
    painter->drawEllipse(boundingRect().adjusted(1,1,-1,-1)); // Left, Top +1 pixel // Width, Height -2 pixel된다.
    painter->setBrush(brushActive);
    painter->drawPie(boundingRect().adjusted(1,1,-1,-1),
                     90*16, m_angle*16); // 16을 곱해줘야 한다!!. 90도 지점부터 m_angle 만큼 움직인다.
    painter->setBrush(brush);
    painter->drawEllipse(boundingRect().adjusted(10,10,-10,-10));
    // QTime m_circleTime 은 QML에서 그린다!
}

void ClockCircle::clear()
{
    setCircleTime(QTime(0,0,0,0));
    setAngle(0);
    update();  // Redraw;, Invalidate();와 같은 느낌이다.
    emit cleared();
}

void ClockCircle::start()
{
    internalTimer->start(50);
}

void ClockCircle::stop()
{
    internalTimer->stop();
}

QString ClockCircle::name() const
{
    return m_name;
}

QColor ClockCircle::backgroundColor() const
{
    return m_backgroundColor;
}

QColor ClockCircle::borderActiveColor() const
{
    return m_borderActiveColor;
}

QColor ClockCircle::borderNonActiveColor() const
{
    return m_borderNonActiveColor;
}

qreal ClockCircle::angle() const
{
    return m_angle;
}

QTime ClockCircle::circleTime() const
{
    return m_circleTime;
}

void ClockCircle::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void ClockCircle::setBackgroundColor(QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(m_backgroundColor);
}

void ClockCircle::setBorderActiveColor(QColor borderActiveColor)
{
    if (m_borderActiveColor == borderActiveColor)
        return;

    m_borderActiveColor = borderActiveColor;
    emit borderActiveColorChanged(m_borderActiveColor);
}

void ClockCircle::setBorderNonActiveColor(QColor borderNonActiveColor)
{
    if (m_borderNonActiveColor == borderNonActiveColor)
        return;

    m_borderNonActiveColor = borderNonActiveColor;
    emit borderNonActiveColorChanged(m_borderNonActiveColor);
}

void ClockCircle::setAngle(qreal angle)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_angle, angle))
        return;
    m_angle = angle;
    if(m_angle <= -360) m_angle =0;
    emit angleChanged(m_angle);
}

void ClockCircle::setCircleTime(QTime circleTime)
{
    if (m_circleTime == circleTime)
        return;

    m_circleTime = circleTime;
    emit circleTimeChanged(m_circleTime);
}
