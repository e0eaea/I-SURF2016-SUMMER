#include "mysquare.h"

Mysquare::Mysquare()
{
     pressed=false;
     setFlag(ItemIsMovable);
}

QRectF Mysquare::boundingRect() const
{
   return QRect(0,0,100,100);
}

void Mysquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec=boundingRect();
    QBrush brush(Qt::blue);

    if(pressed)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);

    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);

}


void Mysquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Mysquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
