#include "mygraphicsview.h"
#include "QDebug"


MyGraphicsView::MyGraphicsView(QWidget *widget):QGraphicsView(widget)
{
    qDebug()<<"this";
    now_point=0;

    scene=new QGraphicsScene();
    scene->setSceneRect(0, 0, 400, 400);

    this->setScene(scene);
    this->setRenderHints(QPainter::Antialiasing);
    this->show();
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton & (now_point<4))
    {
        QPointF point=QPointF(event->pos().x(),event->pos().y());
        points[now_point++]=point;

    }

    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Custom view released";
    QGraphicsView::mouseReleaseEvent(event);
    drawLines();
    update();

}

void MyGraphicsView::new_drawing()
{
    now_point=0; scene->clear();
    points_ellipse.clear();
}

void MyGraphicsView::drawLines()
{

    if(now_point>0 && now_point<=4)
    {
        QPointF pt=points[now_point-1];
        double rad = 5;
        Mypoint *mp=new Mypoint(now_point,QRect(pt.rx(),pt.ry(), rad, rad));
        scene->addItem(mp);
        qDebug()<<mp->rect().topRight()<<"    "<<mp->rect().topLeft();
        points_ellipse.push_back(mp);

        //qDebug()<<pt;
        scene->addItem(mp->getLabel());
    }

    if(now_point==4)
    {

        Mypoint* pt_item=points_ellipse.at(0);
        qDebug()<<pt_item->rect().topRight()<<"    "<<pt_item->rect().topLeft();

        gbi = new MyGraphicBezier(points_ellipse);

        scene->addItem(gbi->getCurves());
    }

}
