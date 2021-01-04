#ifndef ROIITEM_H
#define ROIITEM_H

#include <QObject>
class RoiItem : public QObject
{
    Q_OBJECT
public:
    explicit RoiItem(QObject *parent = nullptr);
    Q_PROPERTY(int idx READ idx WRITE setIdx NOTIFY changedIdx)
    Q_PROPERTY(int roiX READ roiX WRITE setRoiX NOTIFY changedRoiX)
    Q_PROPERTY(int roiY READ roiY WRITE setRoiY NOTIFY changedRoiY)
    Q_PROPERTY(int roiW READ roiW WRITE setRoiW NOTIFY changedRoiW)
    Q_PROPERTY(int roiH READ roiH WRITE setRoiH NOTIFY changedRoiH)
    Q_PROPERTY(int roiA READ roiA WRITE setRoiA NOTIFY changedRoiA)

public:
    int idx() const;
    int roiA() const;
    int roiH() const;
    int roiW() const;
    int roiY() const;
    int roiX() const;

public slots:
    void setRoiA(int roiA);
    void setRoiH(int roiH);
    void setRoiW(int roiW);
    void setRoiY(int roiY);
    void setRoiX(int roiX);
    void setIdx(int idx);

signals:
    void changedRoiA(int roiA);
    void changedRoiH(int roiH);
    void changedRoiW(int roiW);
    void changedRoiY(int roiY);
    void changedRoiX(int roiX);
    void changedIdx(int idx);

private:
    int m_roiA;
    int m_roiH;
    int m_roiW;
    int m_roiY;
    int m_roiX;
    int m_idx;
};

#endif // ROIITEM_H
