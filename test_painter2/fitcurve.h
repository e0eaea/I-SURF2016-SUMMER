#ifndef FITCURVE_H
#define FITCURVE_H

#include <QtGui>
#include "mygraphicbezier.h"
#include <math.h>
#include "common_modules.h"

using namespace std;

class FitCurve : public Common_modules
{
public:
    FitCurve(vector<QPointF *> pixels, double error,int iteration);
    void start_fit_curve();
    vector<MyGraphicBezier *> getCurves() const;

private:
    vector<MyGraphicBezier*> curves;
    vector <QPointF *> pixels;
    double	s_error;
    int max_iter;
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


};

#endif // FITCURVE_H


