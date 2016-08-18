#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <QtGui>
#include "common_modules.h"

using namespace std;

class Measurement : public Common_modules
{
public:
    Measurement(){}
    double NearestPointOnCurve(QPointF P,vector <QPointF> V);

private:
    int		MAXDEPTH = 64;	/*  Maximum depth for recursion */
    int	FindRoots(QPointF* w, int degree,double *t,int depth);
    QPointF	*ConvertToBezierForm(QPointF P, QPointF* V);
    double	ComputeXIntercept(QPointF * V,int degree);
    int	ControlPolygonFlatEnough(QPointF *V, int degree);
    int	CrossingCount(QPointF *V,int degree);
    QPointF	Bezier(QPointF *V,int degree,double t, QPointF *Left,QPointF* Right);
    QPointF	V2ScaleII(QPointF *v, double s);
};

#endif // MEASUREMENT_H
