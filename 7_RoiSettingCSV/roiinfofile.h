#ifndef CROIINFOFILE_H
#define CROIINFOFILE_H

#include <QObject>
#include <QQmlListProperty>
#include "roiitem.h"
#include <QVector>

class CRoiInfoFile : public QObject
{
    Q_OBJECT
public:
    explicit CRoiInfoFile(QObject *parent = nullptr);
    Q_PROPERTY(QQmlListProperty<RoiItem> roiList READ roiList NOTIFY changedRoiList)
    Q_INVOKABLE void addRoi(int idx, int roiX, int roiY, int roiW, int roiH, int roiA);
    Q_INVOKABLE void removeRoi(int idx);
    Q_INVOKABLE void save2File(QString szFilePath);


public:
    QQmlListProperty<RoiItem> roiList();

signals:
    void changedRoiList();

private:
    static void appendRoi(QQmlListProperty<RoiItem>*, RoiItem*);
    static int countRois(QQmlListProperty<RoiItem>*);
    static RoiItem* getRoi(QQmlListProperty<RoiItem>*, int);
    static void clearRois(QQmlListProperty<RoiItem>*);
    void appendCustom(RoiItem*);
    int countCustom();
    RoiItem* getCustom(int);
    void clearCustom();

public:
    QVector<RoiItem*> m_roiList;
};
#endif // CROIINFOFILE_H
