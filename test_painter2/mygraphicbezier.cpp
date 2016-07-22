#include "mygraphicbezier.h"
#include <QDebug>


GraphicsBezierItem *MyGraphicBezier::getBezier_curve() const
{
    return bezier_curve;
}

void MyGraphicBezier::update()
{

    bezier_curve->setControl(1,points_ellipse.at(1)->rect().center());
    bezier_curve->setControl(2,points_ellipse.at(2)->rect().center());
    bezier_curve->update();

    qDebug()<<"finish update";

}

void MyGraphicBezier::setCurve_number(int value)
{
    curve_number = value;
}

int MyGraphicBezier::getCurve_number() const
{
    return curve_number;
}

std::vector<Mypoint *> MyGraphicBezier::getPoints_ellipse() const
{
    return points_ellipse;
}

void MyGraphicBezier::setPoints_ellipse(const std::vector<Mypoint *> &value)
{
    points_ellipse = value;
}

MyGraphicBezier::MyGraphicBezier(const std::vector<Mypoint *>& points,float precision)
{
    points_ellipse=points;
    std::vector<Mypoint *>::iterator i;

    for(i=points_ellipse.begin()+1; i!=points_ellipse.end()-1; i++)
    {
        Mypoint* pt_item=*i;
        pt_item->setFlag(QGraphicsItem::ItemIsMovable);
    }

    bezier_curve= new GraphicsBezierItem(points_ellipse.at(0)->rect().center(),points_ellipse.at(1)->rect().center(),precision);
    bezier_curve->addControl(points_ellipse.at(2)->rect().center());
    bezier_curve->addControl(points_ellipse.at(3)->rect().center());

    //bezier_curve->setFlag(QGraphicsItem::ItemIsFocusable);

    qDebug()<<"finish";

}
