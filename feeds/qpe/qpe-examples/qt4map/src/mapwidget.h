#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsView>
#include "map_layer.h"
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
class QPixmap;
class QLabel;
class QPointF;

class MapWidget : public QGraphicsView
{
    Q_OBJECT
public:
    MapWidget();
    
    void readMap();
    QPointF mapToMap(QPointF);
    
public slots:
    void slotZoom(int);
    
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QMouseEvent *);
   // void mousePressEvent(QMouseEvent *);
public:
    QList<Map_Layer *> mapLayers;
private:
    QPixmap map;
    qreal zoom;
    QLabel *viewCoord;
    QLabel *sceneCoord;
    QLabel *mapCoord;
    
    double x1,y1;	// map lefttop lon&lat
    double x2,y2;	// map rightbottom lon&lat
};
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
#endif 	// MAPWIDGET_H
