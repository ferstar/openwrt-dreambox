#include "map_layer.h"
#include <QDebug>

#include <QObject>
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
Map_Region::Map_Region()
{
    mapPolygon = new QGraphicsPolygonItem();
    regionName = new QGraphicsTextItem();
}

Map_Region::~Map_Region()
{

}

Map_PolyLine::Map_PolyLine()
{

}

Map_Point::Map_Point()
{

}

Map_Layer::Map_Layer()
{
    x1 = 118.61;
    y1 = 31.9174;
    x2 = 118.98;
    y2 = 32.178;
    wx = x2-x1;
    hy = y2-y1;

}

Map_Layer::~Map_Layer()
{
}

QPointF Map_Layer::convertCoord(double x, double y)
{
    QPointF point;
    point = QPointF(((x-x1)/wx)*w-w/2,-(((y-y1)/hy)*h-h/2));
    return point;
}

/*bool Map_Layer::ReadMapEdge()
{
    mapEdge = new Map_Region();
    QPolygonF *polygon;

    polygon = new QPolygonF();
    polygon->append(QPointF(-1000,-1000));
    polygon->append(QPointF(1000,-1000));
    polygon->append(QPointF(1000,1000));
    polygon->append(QPointF(-1000,1000));
    mapEdge->mapPolygon.setPolygon(*polygon);
    mapEdge->mapPolygon.setBrush(QBrush(Qt::white));
    mapEdge->mapPolygon.setPen(QPen(Qt::blue));
}

void Map_Layer::DrawMapEdge(QGraphicsScene *scene)
{
    scene->addItem(&mapEdge->mapPolygon);
    //scene->addItem(&(mapEdge.mapPolygons));
}*/



void Map_Layer::GetLayerItems(QString layname)
{
    ////////////////////////////
    int i;
    mitab_handle handle;
    mitab_feature feature;
    int feature_id, num_fields;
    int featurecount;
    int featuretype;
    QStringList fieldnames;

    qDebug()<<"lay name is"<<layname;
    handle = mitab_c_open(layname.toAscii().data());
    if(handle!=0)
    {
        qDebug()<<"open lay success";
    }
    else
    {
        qDebug()<<"open lay fail";
        return;
    }

    featurecount = mitab_c_get_feature_count(handle);
    qDebug()<<"featurecount="<<featurecount;

    num_fields = mitab_c_get_field_count(handle);
    for(i=0;i<num_fields;i++)
    {
        fieldnames.append(mitab_c_get_field_name(handle,i));
    }
    //for(i=0;i<featurecount;i++)
    //for(i=0;i<2;i++)
    for( feature_id = mitab_c_next_feature_id(handle,-1);
         feature_id != -1;
         feature_id = mitab_c_next_feature_id(handle,feature_id) )
    {
        qDebug()<<"feature id="<<feature_id;
        feature = mitab_c_read_feature(handle,feature_id);
        featuretype = mitab_c_get_type(feature);
        qDebug()<<"feature type is"<<featuretype;
        if(featuretype>=TABFC_Point && featuretype<=TABFC_Ellipse) //如果是可显示对象
        {
            switch(featuretype)
            {
            case TABFC_Point:
                GetPoint(feature,fieldnames);
                break;
            case TABFC_FontPoint:
                qDebug()<<"TABFC_FontPoint";
                break;
            case TABFC_CustomPoint:
                qDebug()<<"TABFC_CustomPoint";
                break;
            case TABFC_Text:
                qDebug()<<"TABFC_Text";
                break;
            case TABFC_Polyline:
                GetPolyLine(feature,fieldnames);
                break;
            case TABFC_Arc:
                qDebug()<<"TABFC_Arc";
                break;
            case TABFC_Region:
                GetRegion(feature,fieldnames);
                break;
            case TABFC_Rectangle:
                qDebug()<<"TABFC_Rectangle";
                break;
            case TABFC_Ellipse:
                qDebug()<<"TABFC_Ellipse";
                break;
            default:
                break;
            }
        }//end if
        mitab_c_destroy_feature(feature);
    }//end for(n=0;n<featurecount;n++)
    mitab_c_close(handle);
}

void Map_Layer::GetPolyLine(mitab_feature feature,QStringList &fields)
{
    Map_PolyLine *mappolyline;
    QGraphicsLineItem *line;
    int parts;
    int vertexs;
    int i,j;
    QList<double> longs; //经度集
    QList<double> lats;  //纬度集
    int pencolor;
    int penpattern;
    int penwidth;
    QPen pen;

    pencolor = mitab_c_get_pen_color(feature);
    penpattern = mitab_c_get_pen_pattern(feature);
    penwidth = mitab_c_get_pen_width(feature);

    pen.setColor(pencolor);
    pen.setStyle(Qt::SolidLine);
    //pen.setBrush(QBrush(QColor(Qt::blue),Qt::CrossPattern));
    /*if(penpattern == 2)
    {
        pen.setStyle(Qt::SolidLine);
    }
    else
    {
        pen.setStyle(Qt::DashLine);
    }*/
    pen.setWidth(penwidth);


    parts = mitab_c_get_parts(feature); //取对象环回折线段数量
    longs.clear();
    lats.clear();
    for(i=0;i<parts;i++)
    {
        vertexs = mitab_c_get_vertex_count(feature,i); //返回对象顶点数
        //qDebug()<<"vertexs="<<vertexs;
        for(j=0;j<vertexs;j++)
        {
            longs.append(mitab_c_get_vertex_x(feature,i,j));
            lats.append(mitab_c_get_vertex_y(feature,i,j));
        }
    }
    if(longs.count()>0 && (longs.count()==lats.count()))
    {
        mappolyline = new Map_PolyLine();
    }
    else
    {
        return;
    }
    for(i=0;i<longs.count()-1;i++)
    {
        line = new QGraphicsLineItem();
        line->setLine(QLineF(convertCoord(longs.at(i),lats.at(i)),convertCoord(longs.at(i+1),lats.at(i+1))));
        //line->setLine(QLineF(convertCoord(lats.at(i),longs.at(i)),convertCoord(lats.at(i+1),longs.at(i+1))));
        line->setPen(pen);
        mappolyline->mapPolyLine.append(line);
    }


    mapPolyLines.append(mappolyline);
}

void Map_Layer::GetRegion(mitab_feature feature,QStringList &fields)
{
    Map_Region *region;
    QPolygonF *polygon;

    Map_Field *field;
    int parts;
    int vertexs;
    int i,j;
    QList<double> longs; //经度集
    QList<double> lats;  //纬度集
    int pencolor;
    int penpattern;
    int penwidth;
    QPen pen;
    int brushcolor;
    int brushpattern;
    //QBrush brush(QColor(Qt::blue));
    QBrush brush(QColor(Qt::black)); //这里比较ds奇怪，必须这样，后面的setColor才起作用

    pencolor = mitab_c_get_pen_color(feature);
    penpattern = mitab_c_get_pen_pattern(feature);
    penwidth = mitab_c_get_pen_width(feature);

    pen.setColor(pencolor);
    pen.setStyle(Qt::SolidLine);
    //pen.setBrush(QBrush(QColor(Qt::blue)));
    /*if(penpattern == 2)
    {
        pen.setStyle(Qt::SolidLine);
    }
    else
    {
        pen.setStyle(Qt::DashLine);
    }*/
    pen.setWidth(penwidth);

    brushcolor = mitab_c_get_brush_fgcolor(feature);
    //qDebug()<<"fg brushcolor="<<brushcolor;
    //brushcolor = mitab_c_get_brush_bgcolor(feature);
    //qDebug()<<"bg brushcolor="<<brushcolor;
    brushpattern = mitab_c_get_brush_pattern(feature);
    //qDebug()<<"brushpattern="<<brushpattern;
    brush.setColor(QColor(brushcolor));

    ////////////////////////////////
    region = new Map_Region();
    ////////////////////////////////

    for(i=0;i<fields.count();i++)
    {
        field = new Map_Field;
        field->fieldName = fields.at(i);
        field->fieldContent = mitab_c_get_field_as_string(feature,i);
        qDebug()<<"fieldName is"<<field->fieldName<<"field content is"<<field->fieldContent;
        region->mapFields.append(field);
        if(field->fieldName == "Name")
        {
            region->regionName->setPlainText(field->fieldContent);

        }
    }
    parts = mitab_c_get_parts(feature); //取对象环回折线段数量
    //qDebug()<<"parts="<<parts;
    longs.clear();
    lats.clear();
    for(i=0;i<parts;i++)
    {

        vertexs = mitab_c_get_vertex_count(feature,i); //返回对象顶点数
        //qDebug()<<"vertexs="<<vertexs;
        for(j=0;j<vertexs;j++)
        {
            longs.append(mitab_c_get_vertex_x(feature,i,j));
            lats.append(mitab_c_get_vertex_y(feature,i,j));
        }
    }
    if(longs.count()>0 && (longs.count()==lats.count()))
    {
        //region = new Map_Region();
        polygon = new QPolygonF();
    }
    else
    {
        return;
    }
    //qDebug()<<"count="<<longs;
    for(i=0;i<longs.count();i++)
    {        
        polygon->append(QPointF(convertCoord(longs.at(i),lats.at(i))));
    }
    if(polygon->count()>0)
    {
        //qDebug()<<"X="<<polygon->boundingRect().center().x()<<"Y="<<polygon->boundingRect().center().y();

        region->regionName->setX(polygon->boundingRect().center().x());
        region->regionName->setY(polygon->boundingRect().center().y());
    }
    region->mapPolygon->setPen(pen);
    region->mapPolygon->setBrush(brush);
    region->mapPolygon->setPolygon(*polygon);
    mapRegions.append(region);
}

void Map_Layer::GetPoint(mitab_feature feature,QStringList &fields)
{
    Map_Point *point;

    int parts;
    int vertexs;
    int i,j;
    QList<double> longs; //经度集
    QList<double> lats;  //纬度集
    int pencolor;
    int penpattern;
    int penwidth;
    QPen pen;
    int brushcolor;
    int brushpattern;
    //QBrush brush(QColor(Qt::blue));
    QBrush brush(QColor(Qt::black)); //这里比较ds奇怪，必须这样，后面的setColor才起作用
    pencolor = mitab_c_get_pen_color(feature);
    penpattern = mitab_c_get_pen_pattern(feature);
    penwidth = mitab_c_get_pen_width(feature);

    pen.setColor(pencolor);
    pen.setStyle(Qt::SolidLine);
    //pen.setBrush(QBrush(QColor(Qt::blue)));
    /*if(penpattern == 2)
    {
        pen.setStyle(Qt::SolidLine);
    }
    else
    {
        pen.setStyle(Qt::DashLine);
    }*/
    pen.setWidth(penwidth);

    brushcolor = mitab_c_get_brush_fgcolor(feature);
    //qDebug()<<"fg brushcolor="<<brushcolor;
    //brushcolor = mitab_c_get_brush_bgcolor(feature);
    //qDebug()<<"bg brushcolor="<<brushcolor;
    brushpattern = mitab_c_get_brush_pattern(feature);
    //qDebug()<<"brushpattern="<<brushpattern;
    brush.setColor(QColor(Qt::lightGray));

    parts = mitab_c_get_parts(feature);
    //qDebug()<<"parts="<<parts;
    longs.clear();
    lats.clear();
    for(i=0;i<parts;i++)
    {
        vertexs = mitab_c_get_vertex_count(feature,i); //返回对象顶点数
        //qDebug()<<"vertexs="<<vertexs;
        for(j=0;j<vertexs;j++)
        {
            longs.append(mitab_c_get_vertex_x(feature,i,j));
            lats.append(mitab_c_get_vertex_y(feature,i,j));
        }
    }
    if(longs.count()>0 && (longs.count()==lats.count()))
    {
        point = new Map_Point();
    }
    else
    {
        return;
    }
    for(i=0;i<longs.count();i++)
    {
        point->mapPoint.setCenter(convertCoord(longs.at(i),lats.at(i)));
    }
    mapPoints.append(point);

}


void Map_Layer::DrawLayer(QGraphicsScene *scene)
{
    DrawMapRegions(scene);
    DrawMapPolyLines(scene);
    DrawMapPoints(scene);
}

void Map_Layer::DrawMapPolyLines(QGraphicsScene *scene)
{
    int i,j;
    for(i=0;i<mapPolyLines.count();i++)
    {
        for(j=0;j<mapPolyLines.at(i)->mapPolyLine.count();j++)
        {
            //qDebug()<<"add line";
            scene->addItem(mapPolyLines.at(i)->mapPolyLine.at(j));
        }
    }
}

void Map_Layer::DrawMapRegions(QGraphicsScene *scene)
{
    int i;
    for(i=0;i<mapRegions.count();i++)
    {
        scene->addItem(mapRegions.at(i)->mapPolygon);
        //scene->addItem(mapRegions.at(i)->regionName);
    }
}

void Map_Layer::DrawMapPoints(QGraphicsScene *scene)
{
    int i;
    for(i=0;i<mapPoints.count();i++)
    {
        scene->addItem(&mapPoints.at(i)->mapPoint);
    }
}

void Map_Layer::DrawText(QGraphicsScene *scene)
{
    int i;
    for(i=0;i<mapRegions.count();i++)
    {
        scene->addItem(mapRegions.at(i)->regionName);
    }
}
/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
