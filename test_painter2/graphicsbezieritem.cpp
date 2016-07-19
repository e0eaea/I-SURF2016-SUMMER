#include "graphicsbezieritem.h"

#include <cassert>
#include <QPainter>
#include <QDebug>
#include <math.h>
#include <QWidget>


const float GraphicsBezierItem::DEFAULT_PRECISION = 0.01f;

GraphicsBezierItem::GraphicsBezierItem(QGraphicsItem *parent) :
    GraphicsBezierItem(QPointF(0,0), QPointF(0,0), parent) {
}

GraphicsBezierItem::GraphicsBezierItem(const QPointF &c1, const QPointF &c2, QGraphicsItem *parent) :
    GraphicsBezierItem(c1, c2, DEFAULT_PRECISION, parent) {
}

GraphicsBezierItem::GraphicsBezierItem(const QPointF &c1, const QPointF &c2, float precision, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    controls({c1,c2}),
    precision(precision) {
    path = new QPainterPath();
    update();
}

void GraphicsBezierItem::addControl(const QPointF &c) {
    controls.insert(controls.end()--, c);
    update();
}

void GraphicsBezierItem::removeControl(std::size_t num) {
    std::size_t size = controls.size();

    if (size <= 2)
        throw std::logic_error("Bezier curve must contain at least 2 control points");

    assert(num < size);
    controls.erase(controls.begin() + num);
    update();
}

void GraphicsBezierItem::setControl(std::size_t num, const QPointF &c) {
    assert(num < controls.size());
    controls[num] = c;
    update();
}


const std::vector<QPointF>& GraphicsBezierItem::getControls() const {
    return controls;
}

const std::vector<QPointF>& GraphicsBezierItem::getCurve() const {
    return curve;
}

float GraphicsBezierItem::getPrecision() const {
    return precision;
}

void GraphicsBezierItem::setPrecision(float value) {
    precision = value;
}

QPen GraphicsBezierItem::getPen() const {
    return pen;
}

void GraphicsBezierItem::setPen(const QPen &value) {
    pen = value;
    updateRect();
}

QRectF GraphicsBezierItem::boundingRect() const {
    return rect;
}

void GraphicsBezierItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    // painter->drawPolyline(curve.data(), curve.size());  //This is draw thing!
    path->moveTo(controls.at(0));
    path->cubicTo(controls.at(1),controls.at(2),controls.at(3));
    painter->strokePath(*path,pen);

}

float GraphicsBezierItem::contains_point(QPointF p, float epsilon)
{
    float min_distance = float(0x7fffffff);
    float t = 0.0;

    while(t < 1.0)
    {
        QPointF point =path->pointAtPercent(t);
        QPointF spline_point = QPointF(point.x(), point.y());
        //        qDebug()<<p<<"  "<<spline_point;
        float distance = this->distance(p, spline_point);
        if (distance < min_distance)
            min_distance = distance;
        t += 0.1;
    }
    //    qDebug()<<min_distance<<epsilon;
    return (min_distance <= epsilon);

}

void GraphicsBezierItem::set_selected(bool selected)
{
    is_select=selected;
}

float  GraphicsBezierItem::distance(QPointF p0,QPointF p1)
{

    float a = p1.rx() - p0.rx();
    float b = p1.ry() - p0.ry();
    return sqrt(a * a + b * b);
}


void GraphicsBezierItem::update() {
    curve.clear();

    for (float t = 0.f ; t <= 1.f ; t += precision)
        curve.push_back(tCurve(controls, t));

    updateRect();
}


//void GraphicsBezierItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
////
//    qDebug()<<this->flags();
//   if(this->flags())
//        qDebug()<<"curve pressed";
//}

//void GraphicsBezierItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
////    if(event->button() == Qt::LeftButton)
//        qDebug()<<"curve release";
//}

void GraphicsBezierItem::updateRect() {
    rect.setRect(0,0,0,0);

    for (QPointF &p : curve) {
        if (p.x() <= rect.left())
            rect.setLeft(p.x());
        else if (p.x() >= rect.right())
            rect.setRight(p.x());

        if (p.y() <= rect.top())
            rect.setTop(p.y());
        else if (p.y() >= rect.bottom())
            rect.setBottom(p.y());
    }
}

QPointF GraphicsBezierItem::tCurve(std::vector<QPointF> points, float t) {
    std::vector<QPointF> npoints;
    std::size_t size = points.size();

    if (size == 1)
        return points[0];
    else {
        for (std::size_t i = 0 ; i < size - 1 ; i++)
            npoints.push_back((points[i+1] - points[i]) * t + points[i]);

        return tCurve(npoints, t);
    }
}



