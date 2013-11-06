#ifndef MAP_LAYER_H
#define MAP_LAYER_H

/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/

#include<QGraphicsPolygonItem>

#include <QGraphicsView>

#include <QLineF>

#include <mitab.h>

#include <mitab_capi.h>
#include "qgraphicsmappoint.h"

struct Map_Field
{
    QString fieldName;
    QString fieldContent;
};

class Map_Region
{
public:
    Map_Region();
    ~Map_Region();
public:
    QList <Map_Field *> mapFields;
    QGraphicsTextItem *regionName;
    QGraphicsPolygonItem *mapPolygon; //电子地图多边形图元
};

class Map_PolyLine
{
public:
    Map_PolyLine();
public:
    //QList<Map_Field *> mapFields;
    QList<QGraphicsLineItem *> mapPolyLine;
};

class Map_Point
{
public:
    Map_Point();
public:
    //QList<Map_Field *> mapFields;
    QGraphicsMapPoint mapPoint;
};

class Map_Layer
{
public:
    Map_Layer();
    ~Map_Layer();

public:
    double x1;//画布左上角代表的经度
    double y1;//画布左上角代表的纬度
    double x2;//画布右下角代表的经度
    double y2;//画布右下角代表的纬度
    double w;//当前显示区域的宽度
    double h;//当前显示区域的高度
    double wx;//当前显示区域经度的范围
    double hy;//当前显示区域纬度的范围

    QPointF convertCoord(double x,double y);//转换函数

public:
    QList<Map_Region *> mapRegions;
    //Map_Region *mapEdge; //地图的边沿
    QList<Map_PolyLine *> mapPolyLines;
    QList<Map_Point *> mapPoints;
    //MIFFile *mifFile;
public:
    //bool ReadMapEdge();
    //void DrawMapEdge(QGraphicsScene *scene);

    void GetLayerItems(QString layname);
    void GetPolyLine(mitab_feature feature,QStringList &fields);
    void GetRegion(mitab_feature feature,QStringList &fields);
    void GetPoint(mitab_feature,QStringList &fields);

    void DrawLayer(QGraphicsScene *scene);
    void DrawMapPolyLines(QGraphicsScene *scene);
    void DrawMapRegions(QGraphicsScene *scene);
    void DrawMapPoints(QGraphicsScene *scene);

    void DrawText(QGraphicsScene *scene);

};
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
#endif // MAP_LAYER_H
