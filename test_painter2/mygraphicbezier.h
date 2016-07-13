#ifndef MYGRAPHICBEZIER_H
#define MYGRAPHICBEZIER_H

#include "graphicsbezieritem.h"
#include "mypoint.h"
#include <QtGui>

class MyGraphicBezier
{
private:
    GraphicsBezierItem *curves;
    std::vector<Mypoint *> points_ellipse;
public:
    MyGraphicBezier(const std::vector<Mypoint *> points);

    GraphicsBezierItem *getCurves() const;
};


#endif // MYGRAPHICBEZIER_H
