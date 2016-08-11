#include "fitcurve.h"

#define DEFAULT_RADIUS 1
#define DEFAULT_PRECISION 0.01
#define MAXPOINTS	1000

FitCurve::FitCurve(vector<QPointF *> pixels, double error,int iteration)
{
    this->pixels=pixels;
    this->s_error=error;
    this->max_iter=iteration;
}

void FitCurve::start_fit_curve()
{
    QPointF tHat1,tHat2;
    tHat1 = ComputeLeftTangent(0);
    qDebug()<<"픽셀사이즈는"<<pixels.size();
    tHat2 = ComputeRightTangent(pixels.size()- 1);
    qDebug()<<"여기는";

    FitCubic(0, pixels.size()- 1, tHat1, tHat2,this->s_error);
    qDebug()<<"여기는2";

}

vector<MyGraphicBezier *> FitCurve::getCurves() const
{
    return curves;
}

void FitCurve::FitCubic(int first, int last, QPointF tHat1, QPointF tHat2, double error)
{
    QPointF* bezCurve; /*Control points of fitted Bezier curve*/
    std::vector<Mypoint *> bezCurve_points;
    double	*u;		/*  Parameter values for point  */
    double	*uPrime;	/*  Improved parameter values */
    double	maxError;	/*  Maximum fitting error	 */
    int		splitPoint;	/*  Point to split point set at	 */
    int		nPts;		/*  Number of points in subset  */
    double	iterationError; /*Error below which you try iterating  */
    int		maxIterations = max_iter; /*  Max times to try iterating  */
    QPointF	tHatCenter;   	/* Unit tangent vector at splitPoint */
    int		i;
    double rad = DEFAULT_RADIUS;
    double precision=DEFAULT_PRECISION;

    iterationError = error * error;
    nPts = last - first + 1;

    /*  Use heuristic if region only has two points in it */
    if (nPts == 2) {
        qDebug()<<"1231";

        double dist = V2DistanceBetween2Points(pixels[last], pixels[first]) / 3.0;
        bezCurve=new QPointF[4];
        bezCurve[0] = *pixels[first];
        bezCurve[3] = *pixels[last];

        V2Add(&bezCurve[0], V2Scale(&tHat1, dist),&bezCurve[1]);
        V2Add(&bezCurve[3], V2Scale(&tHat2, dist),&bezCurve[2]);

        qDebug()<<"C1 "<<bezCurve[1];
        qDebug()<<"C2 "<<bezCurve[2];

        for(i=0; i<4; i++)
        {
            Mypoint *mp=new Mypoint(i+1,QRect(bezCurve[i].rx(),bezCurve[i].ry(), rad, rad));
            bezCurve_points.push_back(mp);
        }

        MyGraphicBezier* gbi = new MyGraphicBezier(bezCurve_points,precision);
        curves.push_back(gbi);
        //  free((void *)bezCurve);
        return;
    }

    /*  Parameterize points, and attempt to fit curve */
    u = ChordLengthParameterize(first, last);
    bezCurve = GenerateBezier(first, last, u, tHat1, tHat2);

    /*  Find max deviation of points to fitted curve */
    maxError = ComputeMaxError(first, last, bezCurve, u, &splitPoint);
    if (maxError < error) {
        for(i=0; i<4; i++)
        {
            Mypoint *mp=new Mypoint(i+1,QRect(bezCurve[i].rx(),bezCurve[i].ry(), rad, rad));
            bezCurve_points.push_back(mp);
        }

        MyGraphicBezier* gbi = new MyGraphicBezier(bezCurve_points,precision);
        curves.push_back(gbi);

        delete u;
        delete bezCurve;
        return;
    }


    /*  If error not too large, try some reparameterization  */
    /*  and iteration */
    if (maxError < iterationError) {
        for (i = 0; i < maxIterations; i++) {
            uPrime = Reparameterize(first, last, u, bezCurve);
            delete bezCurve;
            bezCurve = GenerateBezier(first, last, uPrime, tHat1, tHat2);
            maxError = ComputeMaxError(first, last,bezCurve, uPrime, &splitPoint);
            if (maxError < error) {
                for(int j=0; j<4; j++)
                {
                    Mypoint *mp=new Mypoint(i+1,QRect(bezCurve[j].rx(),bezCurve[j].ry(), rad, rad));
                    bezCurve_points.push_back(mp);
                }

                MyGraphicBezier* gbi = new MyGraphicBezier(bezCurve_points,precision);
                curves.push_back(gbi);
                delete u;
                delete bezCurve;
                delete uPrime;
                return;
            }
            delete u;
            u = uPrime;
        }
    }

    /* Fitting failed -- split at max error point and fit recursively */
    delete u;
    delete bezCurve;
    tHatCenter = ComputeCenterTangent(splitPoint);
    FitCubic(first, splitPoint, tHat1, tHatCenter, error);
    V2Negate(&tHatCenter);
    FitCubic(splitPoint, last, tHatCenter, tHat2, error);
}

double*  FitCurve::Reparameterize(int first,int last,double* u,QPointF* bezCurve)
{
    int 	nPts = last-first+1;
    int 	i;
    double	*uPrime;		/*  New parameter values	*/

    uPrime =  new double[nPts];

    for (i = first; i <= last; i++)
        uPrime[i-first] = NewtonRaphsonRootFind(bezCurve,*pixels[i], u[i-first]);

    return (uPrime);
}

double	FitCurve::NewtonRaphsonRootFind(QPointF *Q,QPointF P,double u)
{
    double 		numerator, denominator;
    QPointF 		Q1[3], Q2[2];	/*  Q' and Q''			*/
    QPointF		Q_u, Q1_u, Q2_u; /*u evaluated at Q, Q', & Q''	*/
    double 		uPrime;		/*  Improved u			*/
    int 		i;

    /* Compute Q(u)	*/
    Q_u = BezierII(3, Q, u);

    /* Generate control vertices for Q'	*/
    for (i = 0; i <= 2; i++) {
        Q1[i].rx() = (Q[i+1].rx() - Q[i].rx()) * 3.0;
        Q1[i].ry() = (Q[i+1].ry() - Q[i].ry()) * 3.0;
    }

    /* Generate control vertices for Q'' */
    for (i = 0; i <= 1; i++) {
        Q2[i].rx() = (Q1[i+1].rx() - Q1[i].rx()) * 2.0;
        Q2[i].ry() = (Q1[i+1].ry() - Q1[i].ry()) * 2.0;
    }

    /* Compute Q'(u) and Q''(u)	*/
    Q1_u = BezierII(2, Q1, u);
    Q2_u = BezierII(1, Q2, u);

    /* Compute f(u)/f'(u) */
    numerator = (Q_u.rx() - P.rx()) * (Q1_u.rx()) + (Q_u.ry() - P.ry()) * (Q1_u.ry());
    denominator = (Q1_u.rx()) * (Q1_u.rx()) + (Q1_u.ry()) * (Q1_u.ry()) +
            (Q_u.rx() - P.rx()) * (Q2_u.rx()) + (Q_u.ry() - P.ry()) * (Q2_u.ry());
    if (denominator == 0.0f) return u;

    /* u = u - f(u)/f'(u) */
    uPrime = u - (numerator/denominator);
    return (uPrime);
}
QPointF	FitCurve::BezierII(int degree,QPointF* V,double t)
{
    int 	i, j;
    QPointF Q;	        /* Point on curve at parameter t	*/
    QPointF* Vtemp;		/* Local copy of control points		*/

    /* Copy array	*/
    Vtemp= new QPointF[degree+1];

    for (i = 0; i <= degree; i++) {
        Vtemp[i] = V[i];
    }

    /* Triangle computation	*/
    for (i = 1; i <= degree; i++) {
        for (j = 0; j <= degree-i; j++) {
            Vtemp[j].rx() = (1.0 - t) * Vtemp[j].rx() + t * Vtemp[j+1].rx();
            Vtemp[j].ry() = (1.0 - t) * Vtemp[j].ry() + t * Vtemp[j+1].ry();
        }
    }

    Q = Vtemp[0];
    delete Vtemp;
    return Q;
}

double FitCurve::B0(double u)
{
    double tmp = 1.0 - u;
    return (tmp * tmp * tmp);
}


double FitCurve::B1(double u)
{
    double tmp = 1.0 - u;
    return (3 * u * (tmp * tmp));
}

double FitCurve::B2(double u)
{
    double tmp = 1.0 - u;
    return (3 * u * u * tmp);
}

double FitCurve::B3(double u)
{
    return (u * u * u);
}

QPointF	FitCurve::ComputeLeftTangent(int end)
{
    QPointF	tHat1;
    tHat1 = V2SubII(*pixels[end+1], *pixels[end]);
    tHat1 = *V2Normalize(&tHat1);
    return tHat1;
}
QPointF	FitCurve::ComputeRightTangent(int end)
{
    QPointF	tHat2;
    tHat2 = V2SubII(*pixels[end-1], *pixels[end]);
    tHat2 = *V2Normalize(&tHat2);
    return tHat2;

}
QPointF	FitCurve::ComputeCenterTangent(int center)
{
    QPointF	V1, V2, tHatCenter;

    V1 = V2SubII(*pixels[center-1], *pixels[center]);
    V2 = V2SubII(*pixels[center], *pixels[center+1]);
    tHatCenter.setX((V1.rx() + V2.rx())/2.0);
    tHatCenter.setY((V1.ry() + V2.ry())/2.0);
    tHatCenter = *V2Normalize(&tHatCenter);
    return tHatCenter;


}
double FitCurve::ComputeMaxError(int first,int last,QPointF* bezCurve, double* u,int* splitPoint)
{

    int		i;
    double	maxDist;		/*  Maximum error		*/
    double	dist;		/*  Current error		*/
    QPointF	P;			/*  Point on curve		*/
    QPointF	v;			/*  Vector from point to curve	*/

    *splitPoint = (last - first + 1)/2;
    maxDist = 0.0;
    for (i = first + 1; i < last; i++) {
        P = BezierII(3, bezCurve, u[i-first]);
        v = V2SubII(P, *pixels[i]);
        dist = V2SquaredLength(&v);
        if (dist >= maxDist) {
            maxDist = dist;
            *splitPoint = i;
        }
    }
    return (maxDist);

}

double*	FitCurve::ChordLengthParameterize(int first,int last){

    int		i;
    double	*u;			/*  Parameterization		*/
    u= new double[last-first+1];
    u[0] = 0.0;
    for (i = first+1; i <= last; i++) {
        u[i-first] = u[i-first-1] +  V2DistanceBetween2Points(pixels[i], pixels[i-1]);
    }

    for (i = first + 1; i <= last; i++) {
        u[i-first] = u[i-first] / u[last-first];
    }

    return(u);
}
QPointF* FitCurve::GenerateBezier(int first, int last, double* uPrime, QPointF tHat1, QPointF tHat2)
{
    int 	i;
    QPointF A[MAXPOINTS][2];	/* Precomputed rhs for eqn	*/
    int 	nPts;			/* Number of pts in sub-curve */
    double 	C[2][2];			/* Matrix C		*/
    double 	X[2];			/* Matrix X			*/
    double 	det_C0_C1,		/* Determinants of matrices	*/
            det_C0_X,
            det_X_C1;
    double 	alpha_l,		/* Alpha values, left and right	*/
            alpha_r;
    QPointF 	tmp;			/* Utility variable		*/
    QPointF* bezCurve;	/* RETURN bezier curve ctl pts	*/
    double  segLength;
    double  epsilon;

    bezCurve = new QPointF[4];
    nPts = last - first + 1;


    /* Compute the A's	*/
    for (i = 0; i < nPts; i++) {

        QPointF		v1, v2;
        v1 = tHat1;
        v2 = tHat2;
        //  printf("원래 값 %d : %f %f @@ %f %f \n",i,v1.x,v1.y,v2.x,v2.y);
        V2Scale(&v1, B1(uPrime[i]));
        V2Scale(&v2, B2(uPrime[i]));
        //  printf("바뀐 값 %d : %f %f @@ %f %f \n\n",i,v1.x,v1.y,v2.x,v2.y);
        A[i][0] = v1;
        A[i][1] = v2;
    }

    /* Create the C and X matrices	*/
    C[0][0] = 0.0;
    C[0][1] = 0.0;
    C[1][0] = 0.0;
    C[1][1] = 0.0;
    X[0]    = 0.0;
    X[1]    = 0.0;

    for (i = 0; i < nPts; i++) {
        C[0][0] += V2Dot(&A[i][0], &A[i][0]);
        C[0][1] += V2Dot(&A[i][0], &A[i][1]);
        /*					C[1][0] += V2Dot(&A[i][0], &A[i][1]);*/
        C[1][0] = C[0][1];
        C[1][1] += V2Dot(&A[i][1], &A[i][1]);

        tmp = V2SubII(*pixels[first + i],
                V2AddII(
                    V2ScaleIII(*pixels[first], B0(uPrime[i])),
                    V2AddII(
                        V2ScaleIII(*pixels[first], B1(uPrime[i])),
                        V2AddII(
                            V2ScaleIII(*pixels[last], B2(uPrime[i])),
                            V2ScaleIII(*pixels[last], B3(uPrime[i]))))));


        X[0] += V2Dot(&A[i][0], &tmp);
        X[1] += V2Dot(&A[i][1], &tmp);
    }

    /* Compute the determinants of C and X	*/
    det_C0_C1 = C[0][0] * C[1][1] - C[1][0] * C[0][1];
    det_C0_X  = C[0][0] * X[1]    - C[1][0] * X[0];
    det_X_C1  = X[0]    * C[1][1] - X[1]    * C[0][1];

    /* Finally, derive alpha values	*/
    alpha_l = (det_C0_C1 == 0) ? 0.0 : det_X_C1 / det_C0_C1;
    alpha_r = (det_C0_C1 == 0) ? 0.0 : det_C0_X / det_C0_C1;

    /* If alpha negative, use the Wu/Barsky heuristic (see text) */
    /* (if alpha is 0, you get coincident control points that lead to
         * divide by zero in any subsequent NewtonRaphsonRootFind() call. */

    segLength = V2DistanceBetween2Points(pixels[last], pixels[first]);
    epsilon = 1.0e-6 * segLength;
    if (alpha_l < epsilon || alpha_r < epsilon)
    {
        /* fall back on standard (probably inaccurate) formula, and subdivide further if needed. */
        double dist = segLength / 3.0;
        bezCurve[0] = *pixels[first];
        bezCurve[3] = *pixels[last];
        V2Add(&bezCurve[0], V2Scale(&tHat1, dist), &bezCurve[1]);
        V2Add(&bezCurve[3], V2Scale(&tHat2, dist), &bezCurve[2]);
        return (bezCurve);
    }

    /*  First and last control points of the Bezier curve are */
    /*  positioned exactly at the first and last data points */
    /*  Control points 1 and 2 are positioned an alpha distance out */
    /*  on the tangent vectors, left and right, respectively */
    bezCurve[0] = *pixels[first];
    bezCurve[3] = *pixels[last];
    V2Add(&bezCurve[0], V2Scale(&tHat1, alpha_l), &bezCurve[1]);
    V2Add(&bezCurve[3], V2Scale(&tHat2, alpha_r), &bezCurve[2]);
    return (bezCurve);
}

QPointF* FitCurve::V2Add(QPointF *a,QPointF *b,QPointF *c)
{
    c->setX(a->rx()+b->rx());
    c->setY(a->ry()+b->ry());
    return(c);
}
QPointF	FitCurve::V2AddII(QPointF a,QPointF b){

    QPointF c;
    c.setX(a.rx() + b.rx()); c.setY(a.ry() + b.ry());
    return (c);

}

QPointF* FitCurve::V2Scale(QPointF *v, double newlen)
{
    double len = V2Length(v);
    if (len != 0.0) { v->setX( v->rx()* newlen/len );  v->setY( v->ry()* newlen/len ); }
    return(v);
}
QPointF	FitCurve::V2ScaleIII(QPointF v,double s)
{
    QPointF result;
    result.setX(v.rx() * s); result.setY(v.ry() * s);
    return (result);
}
QPointF	FitCurve::V2SubII(QPointF a,QPointF b)
{
    QPointF c;
    c.setX(a.rx() - b.rx()); c.setY(a.ry() - b.ry());
    return (c);
}

QPointF *FitCurve::V2Normalize(QPointF *v)
{
    double len = V2Length(v);
    if (len != 0.0) { v->setX(v->rx()/= len);   v->setY(v->ry() /= len); }
    return(v);
}


