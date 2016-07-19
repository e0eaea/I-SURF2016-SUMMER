#ifndef MYPOINT_H
#define MYPOINT_H

#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

class Mypoint:public QGraphicsEllipseItem
{
public:
     Mypoint(int number,QRect rect,QGraphicsEllipseItem *parent=0);
     QGraphicsTextItem *getLabel() const;

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QGraphicsTextItem * label;
    int point_number;
    void update_label();

};

#endif // MYPOINT_H
