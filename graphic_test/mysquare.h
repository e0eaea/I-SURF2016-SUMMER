#ifndef MYSQUARE_H
#define MYSQUARE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>


class Mysquare :public QGraphicsItem
{
public:
    Mysquare();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool pressed;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // MYSQUARE_H
