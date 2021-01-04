#include "rcpinfo.h"
#include <QSettings>
#include <QFile>
#include <QDebug>

RcpInfo::RcpInfo(QObject *parent) : QObject(parent)
{
    if (!QFile::exists(":/res/BattryWInsp.ini"))
        return;
}

void RcpInfo::read()
{
    QSettings settings(":/res/BattryWInsp.ini", QSettings::IniFormat);
    SetStPos(settings.value("INSPMODE1LANE/INSPSTPOS").toDouble());
    SetScanOffset(settings.value("INSPMODE1LANE/SCANOFFSET").toDouble());
    SetInspRange(settings.value("INSPMODE1LANE/INSPRANGE").toDouble());
    SetFilter(settings.value("INSPMODE1LANE/CELLLENGTH").toDouble());
}

void RcpInfo::write()
{
    qDebug() <<"test";
    QSettings settings("C:/Users/jungt/Documents/SrcTreeRepo/QMLTrain/2_ReadFile/res/BattryWInsp.ini", QSettings::IniFormat);
    settings.setValue("INSPMODE1LANE/INSPSTPOS2", m_dStPos);
    settings.setValue("INSPMODE1LANE/SCANOFFSET2", m_dScanOffset);
    settings.setValue("INSPMODE1LANE/INSPRANGE2", m_dInspRange);
    settings.setValue("INSPMODE1LANE/CELLLENGTH2", m_dFilter);
}

double RcpInfo::dStPos() const
{
    return m_dStPos;
}

double RcpInfo::dScanOffset() const
{
    return m_dScanOffset;
}

double RcpInfo::dInspRange() const
{
    return m_dInspRange;
}

double RcpInfo::dFilter() const
{
    return m_dFilter;
}

void RcpInfo::SetStPos(double dStPos)
{
    qDebug()<<"Changed to :" + QString::number(dStPos);
    m_dStPos = dStPos;
    emit changedStPos(m_dStPos);
}

void RcpInfo::SetScanOffset(double dScanOffset)
{
    qDebug()<<"Changed to :" + QString::number(dScanOffset);
    m_dScanOffset = dScanOffset;
    emit changedScanOffset(m_dScanOffset);
}

void RcpInfo::SetInspRange(double dInspRange)
{
    qDebug()<<"Changed to :" + QString::number(dInspRange);
    m_dInspRange = dInspRange;
    emit changedInspRange(m_dInspRange);
}

void RcpInfo::SetFilter(double dFilter)
{
    qDebug()<<"Changed to :" + QString::number(dFilter);
    m_dFilter = dFilter;
    emit changedFilter(m_dFilter);
}
