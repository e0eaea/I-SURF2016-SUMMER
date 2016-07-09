#include "myqgraphicsview.h"
   #include <QPointF>

   MyQGraphicsView::MyQGraphicsView(QWidget *parent) :
       QGraphicsView(parent)
   {
       scene = new QGraphicsScene();
       this->setSceneRect(50, 50, 350, 350);
       this->setScene(scene);
   }

   void MyQGraphicsView::mousePressEvent(QMouseEvent * e)
   {
       double rad = 1;
       QPointF pt = mapToScene(e->pos());
       scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
           QPen(), QBrush(Qt::SolidPattern));
   }
