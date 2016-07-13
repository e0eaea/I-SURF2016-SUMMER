#include "mygraphicbezier.h"
#include <QDebug>


GraphicsBezierItem *MyGraphicBezier::getCurves() const
{
    return curves;
}

MyGraphicBezier::MyGraphicBezier(const std::vector<Mypoint *> points)
{
    points_ellipse=points;
    std::vector<Mypoint *>::iterator vi;

    for(vi=points_ellipse.begin()+1; vi!=points_ellipse.end()-1; vi++)
    {
        Mypoint* pt_item=*vi;
        pt_item->setFlag(QGraphicsItem::ItemIsMovable);
    }

    curves= new GraphicsBezierItem(points_ellipse.at(0)->rect().center(),points_ellipse.at(1)->rect().center());

    curves->addControl(points_ellipse.at(2)->rect().center());
    curves->addControl(points_ellipse.at(3)->rect().center());


    qDebug()<<"finish";



}
