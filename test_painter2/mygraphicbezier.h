#ifndef MYGRAPHICBEZIER_H
#define MYGRAPHICBEZIER_H

#include "graphicsbezieritem.h"
#include "mypoint.h"
#include <QtGui>

class MyGraphicBezier
{
private:
    GraphicsBezierItem *bezier_curve;
    std::vector<Mypoint *> points_ellipse;
    int curve_number;
public:
    MyGraphicBezier(const std::vector<Mypoint *> &points);
    GraphicsBezierItem *getBezier_curve() const;
    void update();
    int getCurve_number() const;
    void setCurve_number(int value);
    std::vector<Mypoint *> getPoints_ellipse() const;
    void setPoints_ellipse(const std::vector<Mypoint *> &value);
};


#endif // MYGRAPHICBEZIER_H
