#ifndef FITCURVE_H
#define FITCURVE_H

#include <QtGui>
#include "mygraphicbezier.h"
#include <math.h>

using namespace std;

class FitCurve
{
public:
    FitCurve(vector <QPointF *>  ㅇㅇㅇpixels,double error);
    void start_fit_curve();
    vector<MyGraphicBezier *> getCurves() const;

private:
    vector<MyGraphicBezier*> curves;
    vector <QPointF *> pixels;
    double	error;
    void FitCubic(int first,int last,QPointF tHat1,QPointF tHat2,double error);
    double *Reparameterize(int first,int last,double* u,QPointF* bezCurve);
    double NewtonRaphsonRootFind(QPointF *Q, QPointF P, double u);
    QPointF BezierII(int degree,QPointF* V,double t);
    double B0(double u), B1(double u), B2(double u), B3(double u);
    QPointF	ComputeLeftTangent(int end);
    QPointF	ComputeRightTangent(int end);
    QPointF	ComputeCenterTangent(int center);
    double	ComputeMaxError(int first,int last,QPointF* bezCurve, double* u,int* splitPoint);
    double	*ChordLengthParameterize(int first,int last);
    QPointF* GenerateBezier(int first,int last, double *uPrime, QPointF tHat1,QPointF tHat2);
    QPointF *V2Add(QPointF *a,QPointF *b,QPointF *c);
    QPointF	V2AddII(QPointF a,QPointF b);
    QPointF* V2Scale(QPointF *v,double newlen);
    QPointF	V2ScaleIII(QPointF v,double s);
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

#endif // FITCURVE_H


