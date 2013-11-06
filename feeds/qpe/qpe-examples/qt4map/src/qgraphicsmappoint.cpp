#include "qgraphicsmappoint.h"
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
QGraphicsMapPoint::QGraphicsMapPoint()
{
    radius = 2;
}

QRectF QGraphicsMapPoint::boundingRect() const
{

    return QRectF(-radius,-radius,2*radius,2*radius);
}

void QGraphicsMapPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPointF points[4] = {
        QPointF(centerPoint.x()-radius,centerPoint.y()),
        QPointF(centerPoint.x(),centerPoint.y()+radius),
        QPointF(centerPoint.x()+radius,centerPoint.y()),
        QPointF(centerPoint.x(),centerPoint.y()-radius),
    };
    painter->setPen(Qt::black);
    painter->setBrush(Qt::yellow);
    painter->drawPolygon(points,4);

}

void QGraphicsMapPoint::setCenter(const QPointF &point)
{
    centerPoint = point;
}
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
