#include "roiitem.h"

RoiItem::RoiItem(QObject *parent) : QObject(parent)
{

}

int RoiItem::roiA() const
{
    return m_roiA;
}

int RoiItem::roiH() const
{
    return m_roiH;
}

int RoiItem::roiW() const
{
    return m_roiW;
}

int RoiItem::roiY() const
{
    return m_roiY;
}

int RoiItem::roiX() const
{
    return m_roiX;
}

int RoiItem::idx() const
{
    return m_idx;
}

void RoiItem::setRoiA(int roiA)
{
    if (m_roiA == roiA)
        return;

    m_roiA = roiA;
    emit changedRoiA(m_roiA);
}

void RoiItem::setRoiH(int roiH)
{
    if (m_roiH == roiH)
        return;

    m_roiH = roiH;
    emit changedRoiH(m_roiH);
}

void RoiItem::setRoiW(int roiW)
{
    if (m_roiW == roiW)
        return;

    m_roiW = roiW;
    emit changedRoiW(m_roiW);
}

void RoiItem::setRoiY(int roiY)
{
    if (m_roiY == roiY)
        return;

    m_roiY = roiY;
    emit changedRoiY(m_roiY);
}

void RoiItem::setRoiX(int roiX)
{
    if (m_roiX == roiX)
        return;

    m_roiX = roiX;
    emit changedRoiX(m_roiX);
}

void RoiItem::setIdx(int idx)
{
    if (m_idx == idx)
        return;

    m_idx = idx;
    emit changedIdx(m_idx);
}
