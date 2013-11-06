#ifndef QGRAPHICSMAPPOINT_H
#define QGRAPHICSMAPPOINT_H

#include <QGraphicsItem>
#include <QPainter>
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
class QGraphicsMapPoint : public QGraphicsItem
{
public:
    QGraphicsMapPoint();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCenter(const QPointF & point);
public:
    QPointF centerPoint;
    int radius;
};
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
#endif // QGRAPHICSMAPPOINT_H
