#include "roiinfofile.h"
#include <QDebug>
#include <QFile>
#include <QQmlListProperty>

CRoiInfoFile::CRoiInfoFile(QObject *parent) : QObject(parent)
{
    qDebug() << "roiInfo Read!";
    QFile file(":/res/RoiInfo.csv");
    if(file.open(QIODevice::ReadOnly)){
        QString line;
        QTextStream t(&file);
        do{
            line = t.readLine();
            if(line.size()!=0){
                QRegExp rx("[, ]");// match a comma or a space
                QStringList list = line.split(rx, QString::SkipEmptyParts);
                RoiItem *roi = new RoiItem(this);
                roi->setIdx(list.at(0).toInt());
                roi->setRoiX(list.at(1).toInt());
                roi->setRoiY(list.at(2).toInt());
                roi->setRoiW(list.at(3).toInt());
                roi->setRoiH(list.at(4).toInt());
                roi->setRoiA(list.at(5).toInt());
                m_roiList.append(roi);
            }
        }while(!line.isNull());
        file.close();
    }
}

void CRoiInfoFile::addRoi(int idx, int roiX, int roiY, int roiW, int roiH, int roiA)
{
    RoiItem *roi = new RoiItem(this);
    roi->setIdx(idx);
    roi->setRoiX(roiX);
    roi->setRoiY(roiY);
    roi->setRoiW(roiW);
    roi->setRoiH(roiH);
    roi->setRoiA(roiA);
    m_roiList.append(roi);
    this->changedRoiList();
}

void CRoiInfoFile::removeRoi(int idx)
{
    m_roiList.removeAt(idx);
    this->changedRoiList();
}

void CRoiInfoFile::save2File(QString szFilePath)
{
    qDebug()<< szFilePath;
    QFile file("test.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        for(int i =0; i < m_roiList.size(); i++)
        {
            QString szRoiInfo;
            auto roi = m_roiList.at(i);
            szRoiInfo=QString("%1, %2, %3, %4, %5, %6\n").arg(QString::number(roi->idx()),QString::number(roi->roiX()),QString::number(roi->roiY()))
                    .arg(QString::number(roi->roiW()),QString::number(roi->roiH()),QString::number(roi->roiA()));
            file.write(szRoiInfo.toUtf8());
        }
    }
    file.close();
    qDebug()<<"File Write Done";
}

QQmlListProperty<RoiItem> CRoiInfoFile::roiList()
{
    return QQmlListProperty<RoiItem>(this,this,&CRoiInfoFile::appendRoi,
                                     &CRoiInfoFile::countRois,
                                     &CRoiInfoFile::getRoi,
                                     &CRoiInfoFile::clearRois);
}

void CRoiInfoFile::appendRoi(QQmlListProperty<RoiItem>* listRoi, RoiItem *roiItem)
{
    reinterpret_cast<CRoiInfoFile*>(listRoi->data)->appendCustom(roiItem);
}

int CRoiInfoFile::countRois(QQmlListProperty<RoiItem>* listRoi)
{
    return reinterpret_cast<CRoiInfoFile*>(listRoi->data)->countCustom();
}

RoiItem *CRoiInfoFile::getRoi(QQmlListProperty<RoiItem>* listRoi, int index)
{
    return reinterpret_cast<CRoiInfoFile*>(listRoi->data)->getCustom(index);
}

void CRoiInfoFile::clearRois(QQmlListProperty<RoiItem>* listRoi)
{
    reinterpret_cast<CRoiInfoFile*>(listRoi->data)->clearCustom();
}

void CRoiInfoFile::appendCustom(RoiItem *roiItem)
{
    m_roiList.append(roiItem);
}

int CRoiInfoFile::countCustom()
{
    return m_roiList.count();
}

RoiItem* CRoiInfoFile::getCustom(int index)
{
    return m_roiList.at(index);
}

void CRoiInfoFile::clearCustom()
{
    m_roiList.clear();
}

