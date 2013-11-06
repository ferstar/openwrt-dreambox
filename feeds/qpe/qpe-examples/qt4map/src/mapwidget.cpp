#include "mapwidget.h"
#include <QtGui>
#include <math.h>

/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/
MapWidget::MapWidget()
{
    //这两句将窗口居中
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //////////////////////////////////////////////////////////////
    setMouseTracking(true);
    //readMap();
    x1 = 118.61;
    y1 = 31.9174;
    x2 = 118.98;
    y2 = 32.178;

//    map.load(":/images/map.png");
    zoom = 50;
    
    //qDebug()<<"map.width="<<map.width();
    //qDebug()<<"map.height="<<map.height();

    int width = map.width();
    int height = map.height();

    width = 2000;
    height = 2000;
    
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-width/2,-height/2,width,height);
    scene->setSceneRect(-width/2,-height/2,width,height);
    //  setInteractive(0);
    setScene(scene);
    //setRenderHint(QPainter::Antialiasing);
  //  setBackgroundBrush(QPixmap(":/images/map.png"));
    setCacheMode(CacheBackground);
    //  setInteractive(0);

    Map_Layer *layer;
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/Adm_Area.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    /////////////////////////////////
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/Landuse.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    //////////////////////////////
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/RailWay.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    ///////////////////////////////
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/Block.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    ///////////////////////////////
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/Road.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    ///////////////////////////////
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/Adm_LandMark.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    ///////////////////////////////
    layer = new Map_Layer();
    layer->w = width;
    layer->h = height;
    layer->GetLayerItems("./maps/Node.mif");
    layer->DrawLayer(scene);
    mapLayers.append(layer);
    ///////////////////////////////
    for(int i=0;i<mapLayers.count();i++)
    {
        mapLayers.at(i)->DrawText(scene);
    }
     
    QSlider *slider = new QSlider;
    slider->setOrientation(Qt::Vertical);
    slider->setRange(1,100);
    slider->setTickInterval(10);
    slider->setValue(50);
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slotZoom(int)));
    
    QLabel *zoominLabel = new QLabel;
    zoominLabel->setScaledContents(true);
    zoominLabel->setPixmap(QPixmap(":/images/zoomin.png"));
    
    QLabel *zoomoutLabel = new QLabel;
    zoomoutLabel->setScaledContents(true);
    zoomoutLabel->setPixmap(QPixmap(":/images/zoomout.png"));
    
    //  create coordinate area
    QFrame *coordFrame = new QFrame;
    QLabel *label1 = new QLabel(tr("GraphicsView :"));
    viewCoord = new QLabel;
    QLabel *label2 = new QLabel(tr("GraphicsScene :"));
    sceneCoord = new QLabel;
    QLabel *label3 = new QLabel(tr("map :"));
    mapCoord = new QLabel;
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(label1,0,0);
    grid->addWidget(viewCoord,0,1);
    grid->addWidget(label2,1,0);
    grid->addWidget(sceneCoord,1,1);
    grid->addWidget(label3,2,0);
    grid->addWidget(mapCoord,2,1);
    grid->setSizeConstraint(QLayout::SetFixedSize);
    coordFrame->setLayout(grid);
    
    //  zoom layout
    QVBoxLayout *zoomLayout = new QVBoxLayout;
    zoomLayout->addWidget(zoominLabel);
    zoomLayout->addWidget(slider);
    zoomLayout->addWidget(zoomoutLabel);
    
    //  coordinate area layou
    QVBoxLayout *coordLayout = new QVBoxLayout;
    coordLayout->addWidget(coordFrame);
    coordLayout->addStretch();
        
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(zoomLayout);
    layout->addLayout(coordLayout);
    layout->addStretch();
    layout->setMargin(30);
    layout->setSpacing(10);
    setLayout(layout);
    
    setWindowTitle("Map Widget");
    setMinimumSize(600,400);
}

// read map information
void MapWidget::readMap()
{
    QFile mapFile("maps.txt"); 
    QString mapName;
    int ok = mapFile.open(QIODevice::ReadOnly);
    if (ok)
    {
    	QTextStream t(&mapFile);
    	if (!t.atEnd())
    	{
    	    t >> mapName;
    	    t >> x1 >> y1 >> x2 >> y2;
    	}
    }
  
    map.load(mapName);
    if (map.isNull())
    	printf("map is null");
}

void MapWidget::slotZoom(int value)
{
//		setInteractive(1);
    qreal s;
    if (value>zoom)	// zoom in
    {
        s = pow(1.04,(value-zoom));
    }
    else		// zoom out
    {
        s = pow((1/1.04),(zoom-value));
    }

    scale(s,s);
    zoom = value;
}

void MapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    //painter->drawPixmap(int(sceneRect().left()),int(sceneRect().top()),map);
}

void MapWidget::mouseMoveEvent(QMouseEvent * event)
{
    //qDebug()<<"mouse move event";
    // view coordinate
    QPoint viewPoint = event->pos();
    viewCoord->setText(QString::number(viewPoint.x()) + ", " + QString::number(viewPoint.y()));
    
    // scene coordinate
    QPointF scenePoint = mapToScene(viewPoint);
    sceneCoord->setText(QString::number(scenePoint.x()) + ", " + QString::number(scenePoint.y()));
    
    // map coordinate
    QPointF latLon = mapToMap(scenePoint);
    mapCoord->setText(QString::number(latLon.x()) + ", " + QString::number(latLon.y()));
}

// map scene coordinate to map
QPointF MapWidget::mapToMap(QPointF p)
{
    QPointF latLon;
    qreal w = sceneRect().width();
    qreal h = sceneRect().height();
    qreal lon = y1 - ((h/2 + p.y())*(y2-y1)/h);
    qreal lat = x1 + ((w/2 + p.x())*(x2-x1)/w);
    latLon.setX(lat);
    latLon.setY(lon);
    return latLon;
    
}

/*
write by hugerat Email:njjqs115@jlonline.com
2011-02-28
*/

