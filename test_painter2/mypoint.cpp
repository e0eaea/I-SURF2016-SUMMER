#include "mypoint.h"
#include <QDebug>


Mypoint::Mypoint(int number, QRect rect, QGraphicsEllipseItem *parent):QGraphicsEllipseItem(rect,parent)
{
    label = new QGraphicsTextItem();
    this->point_number=number;
    this->setPen( QPen());
    this->setBrush(QBrush(Qt::SolidPattern));
    update_label();

}

void Mypoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->flags())
        if(event->button() == Qt::LeftButton)
            qDebug() << "Pressed";

}

void Mypoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if (this->flags() &&event->button() == Qt::LeftButton){
        qDebug()<<"release!";
        QPointF point=QPointF(event->scenePos());
        this->setRect(point.x(),point.y(),this->rect().size().width(),this->rect().size().height());
        this->setPos(0,0);
       // qDebug()<< "마우스 놓았을때 "<<this->rect().topLeft()<<"위치"<<this->pos()<<"이벤트위치"<<point ;
        update_label();
        update();

    }


}

QGraphicsTextItem *Mypoint::getLabel() const
{
    return label;
}

void Mypoint::update_label()
{
    QPointF point=this->rect().topLeft();
    label->setPos(point);
    QString s;
    s.sprintf("p %d",point_number);
    label->setPlainText(s);


}

