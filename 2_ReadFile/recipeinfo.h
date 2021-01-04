#ifndef RECIPEINFO_H
#define RECIPEINFO_H

#include <QObject>
class RecipeInfo : public QObject
{
    Q_OBJECT

public:
    explicit RecipeInfo(QObject *parent = nullptr);
    Q_PROPERTY(double dStPos READ dStPos WRITE SetStPos)
    Q_PROPERTY(double dScanOffset READ dScanOffset WRITE SetScanOffset)
    Q_PROPERTY(double dInspRange READ dInspRange WRITE SetInspRange)
    Q_PROPERTY(double dFilter READ dFilter WRITE SetFilter)
public:
    RecipeInfo();
    double dStPos() const;
    double dScanOffset() const;
    double dInspRange() const;
    double dFilter() const;

public slots:
    void SetStPos(double dStPos);
    void SetScanOffset(double dScanOffset);
    void SetInspRange(double dInspRange);
    void SetFilter(double dFilter);
private:
    double m_dStPos;
    double m_dScanOffset;
    double m_dInspRange;
    double m_dFilter;
};
//Q_DECLARE_METATYPE(RecipeInfo)
#endif // RECIPEINFO_H
