#include "node_pixel.h"

Node_pixel::Node_pixel(QPointF* pixel,double max_distance):QPointF(pixel)
{
    this->max_distance=max_distance;
}

Node_pixel *Node_pixel::getPre() const
{
    return pre;
}

void Node_pixel::setPre(Node_pixel *value)
{
    pre = value;
}

Node_pixel *Node_pixel::getNext() const
{
    return next;
}

void Node_pixel::setNext(Node_pixel *value)
{
    next = value;
}

QPointF *Node_pixel::getP() const
{
    return p;
}

void Node_pixel::setP(QPointF *value)
{
    this= value;
}

double Node_pixel::distance(QPointF *b)
{
    double x=this->rx()-b->rx();
    double y=this->ry()-b->ry();

    return (x*x +y*y);
}
