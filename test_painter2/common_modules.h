#ifndef COMMON_MODULES_H
#define COMMON_MODULES_H

#include <QtGui>
#include <math.h>

class Common_modules
{
public:
    Common_modules();

    QPointF *V2Add(QPointF *a,QPointF *b,QPointF *c);
    QPointF	V2AddII(QPointF a,QPointF b);
    QPointF* V2Scale(QPointF *v,double newlen);
    QPointF	V2ScaleIII(QPointF v,double s);
    QPointF *V2Sub(QPointF *a,QPointF * b, QPointF *c);
    QPointF	V2SubII(QPointF a,QPointF b);
    QPointF *V2Normalize(QPointF* v);
    double V2SquaredLength(QPointF* a){	return((a->rx() * a->rx())+(a->ry() * a->ry())); }
    double V2Length(QPointF* a){ return(sqrt(V2SquaredLength(a))); }
    QPointF *V2Negate(QPointF* v){ v->setX(-v->rx());  v->setY(-v->ry()); return(v); }

    double V2DistanceBetween2Points(QPointF *a,QPointF *b)
    {
        double dx = a->rx() - b->rx();
        double dy = a->ry() - b->ry();
        return(sqrt((dx*dx)+(dy*dy)));
    }
    double V2Dot(QPointF* a,QPointF* b)
    {
        return((a->rx()*b->rx())+(a->ry()*b->ry()));
    }
};

#endif // COMMON_MODULES_H
