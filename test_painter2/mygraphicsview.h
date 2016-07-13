#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include<QtGui>

#include <QGraphicsScene>
#include "mygraphicbezier.h"


class MyGraphicsView: public QGraphicsView
{
public:
    MyGraphicsView(QWidget *widget);
    void new_drawing();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    MyGraphicBezier *gbi;
    QGraphicsScene *scene;
    std::vector<Mypoint *> points_ellipse;
    QPointF points[4];
    int now_point;
    void drawLines();

};

#endif // MYGRAPHICSVIEW_H
