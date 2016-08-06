#ifndef NODE_PIXEL_H
#define NODE_PIXEL_H

#include <QtGui>

class Node_pixel:QPointF
{
public:
    Node_pixel(QPointF* pixel,double max_distance);
    Node_pixel *getPre() const;
    void setPre(Node_pixel *value);

    Node_pixel *getNext() const;
    void setNext(Node_pixel *value);

    QPointF *getP() const;
    void setP(QPointF *value);

private:
    double max_distance;
    Node_pixel *pre;
    Node_pixel *next;
    double distance(QPointF* b);
};

#endif // NODE_PIXEL_H
