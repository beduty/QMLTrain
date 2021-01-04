#include "drawingpainter.h"
#include "drawingitem.h"
DrawingPainter::DrawingPainter()
{

}

void DrawingPainter::paint(QNanoPainter *painter)
{
    // 배경과 테두리를 그린다.
    QNanoRadialGradient grad;
    grad.setStartColor("#808080");
    grad.setEndColor("#606060");
    grad.setCenterPosition(width()/2, height()/2);
    grad.setOuterRadius(qMax(width(), height())*0.6f);
    painter->setFillStyle(grad);
    painter->setStrokeStyle("#F0F0F0");
    painter->setLineWidth(1);
    painter->beginPath();
    painter->rect(0,0,width(), height());
    painter->fill();
    painter->stroke();

    //QQueue<QSharedPointer<Path>> m_paths;를 그린다.
    // m_paths는 DrawingItem 클래스에서 MousePressed될 때, 추가된다.
    // DrawingItem::m_pointsSynced가 0일때 추가된다.
    // MouseReleased될 때, 마지막 Point로 INT_MAX를 추가하여
    //  m_path의 LastData의 추가가 끝났음을 알린다. -> HideAnimation을 켠다.
    if(m_paths.size() > 0)
    {
        painter->setLineCap(QNanoPainter::CAP_ROUND);
        painter->setLineJoin(QNanoPainter::JOIN_ROUND);
         // 화면 크기가 변경되어도, 2mm 굵기의 선이 되도록 보장한다.
        float lineWidth = QNanoPainter::mmToPx(2);
        painter->setLineWidth(lineWidth);

        //QQueue<QSharedPointer<Path>> m_paths;를 그린다.
        for(int i =0; i<m_paths.count(); ++i)
        {
            auto item = m_paths.at(i).data();
            auto points = item->m_points;
            if(points.count()>0)
            {
                // 선의 그림자를 그린다.
                QNanoColor shadowColor("#202020");
                shadowColor.setAlpha(item->opacity()*200);
                painter->setStrokeStyle(shadowColor);
                painter->setAntialias(10.0);
                drawPathLine(points, QPoint(lineWidth*0.2, lineWidth*0.2));

                QNanoColor lineColor("#F0D060");
                // HideAnimation이 시작하면서 item->opacity()가 변경된다.
                // 이에 맞게 화면에 점차 사라진다.
                lineColor.setAlpha(item->opacity()*255);
                painter->setStrokeStyle(lineColor);
                painter->setAntialias(2.0);
                drawPathLine(points, QPoint(0,0));

                if(item->m_hideAnimation.state() == QAbstractAnimation::Running)
                {
                    // HideAnimation이 동작하면 Update가 되고, Animation진행되면서
                    // opacity가 계속 변경되므로 update가 연속으로 이루어진다.
                    // 끝나면 QAbstractAnimation::Finished 이므로 Update가 끝난다.
                    Q_EMIT update();
                }
            }
        }
    }
}

void DrawingPainter::synchronize(QNanoQuickItem *item)
{
    // DrawingItem::update()될 때, 호출된다.
    DrawingItem* realItem = static_cast<DrawingItem*>(item);
    if(realItem)
    {
        //realItem->m_pointsSynced 가 0이면 새로운 라인이므로,
        // QQueue<QSharedPointer<Path>> m_paths;를 추가한다. append()
        if(realItem->m_pointsSynced ==0){
            QSharedPointer<Path> newPath = QSharedPointer<Path>::create();
            m_paths.append(newPath);
        }

        // 가장 최근에 추가된 Path를 받아온다. mouaseMove하면 추가한 QPoint를
        // 해당 Path의 멤버변수인 QVector<QPoint> m_points;에 추가한다.
        auto path = m_paths.last().data();

        if(realItem->m_points.count() > 0 && realItem->m_points.last().x()==INT_MAX)
        {
            QObject::connect(&path->m_hideAnimation, &QAbstractAnimation::finished, [=](){
                // Queue는 선입선출 구조이므로, QQueue<QSharedPointer<Path>> m_paths;
                // 타이머가 끝나면 가장 처음 데이터를 지워야한다.
                m_paths.removeFirst();
            });
            path->m_hideAnimation.start();
            realItem->m_points.removeLast(); // 마지막 INT_MAX를 지운다. 안그려지도록.
        }
        // qDebug() << "point Sync : " << realItem->m_pointsSynced;
        // qDebug() << "point Size : " << realItem->m_points.count();;
        for(int i = realItem->m_pointsSynced; i < realItem->m_points.count(); ++i)
        {
            // 가장 최근 데이터를 Path클래스의 QVector<QPoint> m_points;에 데이터 넣는다.
            path->m_points.append(realItem->m_points.at(i));
        }

        // m_pointsSynced를 업데이트하여 0이 되지 않도록 한다.
        // MouseRelease될 때, 0으로 하여 다음 MousePressed될 때,
        // QQueue<QSharedPointer<Path>> m_paths;에 Path를 추가한다.
        realItem->m_pointsSynced = path->m_points.count();
    }
}

void DrawingPainter::drawPathLine(const QVector<QPoint> &points, const QPoint translate)
{
    // QQueue<QSharedPointer<Path>> m_paths; 데이터를 그린다.
    painter()->beginPath();
    QPoint firstPoint = points.first()+translate;
    painter()->moveTo(firstPoint.x(), firstPoint.y()-1); // 시작점 그린다.
    painter()->lineTo(firstPoint);
    for(int i = 1; i < points.size(); ++i)
    {
        painter()->lineTo(points.at(i) + translate);
    }
    painter()->stroke();
}
