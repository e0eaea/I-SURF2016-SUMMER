#include "common_modules.h"

Common_modules::Common_modules()
{

}


QPointF* Common_modules::V2Add(QPointF *a,QPointF *b,QPointF *c)
{
    c->setX(a->rx()+b->rx());
    c->setY(a->ry()+b->ry());
    return(c);
}
QPointF	Common_modules::V2AddII(QPointF a,QPointF b){

    QPointF c;
    c.setX(a.rx() + b.rx()); c.setY(a.ry() + b.ry());
    return (c);

}

QPointF* Common_modules::V2Scale(QPointF *v, double newlen)
{
    double len = V2Length(v);
    if (len != 0.0) { v->setX( v->rx()* newlen/len );  v->setY( v->ry()* newlen/len ); }
    return(v);
}
QPointF	Common_modules::V2ScaleIII(QPointF v,double s)
{
    QPointF result;
    result.setX(v.rx() * s); result.setY(v.ry() * s);
    return (result);
}

QPointF *Common_modules::V2Sub(QPointF *a, QPointF *b, QPointF *c)
{
    c->setX(a->rx() - b->rx()); c->setY(a->ry() - b->ry());
    return (c);
}


QPointF	Common_modules::V2SubII(QPointF a,QPointF b)
{
    QPointF c;
    c.setX(a.rx() - b.rx()); c.setY(a.ry() - b.ry());
    return (c);
}

QPointF *Common_modules::V2Normalize(QPointF *v)
{
    double len = V2Length(v);
    if (len != 0.0) { v->setX(v->rx()/= len);   v->setY(v->ry() /= len); }
    return(v);
}
