#ifndef RCPINFO_H
#define RCPINFO_H

#include <QObject>

class RcpInfo : public QObject
{
    Q_OBJECT
public:
    explicit RcpInfo(QObject *parent = nullptr);
    Q_PROPERTY(double dStPos READ dStPos WRITE SetStPos NOTIFY changedStPos)
    Q_PROPERTY(double dScanOffset READ dScanOffset WRITE SetScanOffset NOTIFY changedScanOffset)
    Q_PROPERTY(double dInspRange READ dInspRange WRITE SetInspRange NOTIFY changedInspRange)
    Q_PROPERTY(double dFilter READ dFilter WRITE SetFilter NOTIFY changedFilter)
    Q_INVOKABLE void read();
    Q_INVOKABLE void write();

    double dStPos() const;
    double dScanOffset() const;
    double dInspRange() const;
    double dFilter() const;

public slots:
    void SetStPos(double dStPos);
    void SetScanOffset(double dScanOffset);
    void SetInspRange(double dInspRange);
    void SetFilter(double dFilter);

signals:
    void changedStPos(double dStPos);
    void changedScanOffset(double dScanOffset);
    void changedInspRange(double dInspRange);
    void changedFilter(double dFilter);

private:
    double m_dStPos;
    double m_dScanOffset;
    double m_dInspRange;
    double m_dFilter;
};

#endif // RCPINFO_H
