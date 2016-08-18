#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QMainWindow>
#include<QtGui>
#include<QtCore>
#include <QGraphicsScene>
#include "mygraphicbezier.h"
#include "fitcurve.h"
#include "measurement.h"

using namespace std;
class MyGraphicsView: public QGraphicsView
{
public:
    MyGraphicsView(QMainWindow *mv,QWidget *widget);
    void new_drawing();
    void add_drawing();
    void add_curve(QString string);
    void convert_image_to_point(vector <QPointF *> pixels,int min_d=100,double fit_error=100,int iteration=4);
    void clear_points_label();
    void draw_points_label(int num);
    bool getIs_drawing() const;
    bool getIs_selecting() const;
    void setIs_selecting(bool value);
    void set_original_pixels(vector <QPointF *> *pixels);
    void check_measurement();
    vector<MyGraphicBezier *> getCurves() const;

    QGraphicsScene *getScene() const;

    int getNow_point() const;
    void setNow_point(int value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QMainWindow *mv;
    MyGraphicBezier *gbi;

    vector <QPointF *> original_pixels;
    vector<MyGraphicBezier*> curves;
    QGraphicsScene *scene;
    vector<Mypoint *> points_ellipse;
    QPointF points[4];
    int now_point;
    vector < vector <QPointF *> *> group_pixels;

    bool is_drawing;
    bool is_selecting;
    float epsilon;
    int min_d;
    double fit_error;
    int fit_iter;
    void drawLines();
    void select_item_at(QPoint p);
    void unselect_items();
    vector<double>split(QString str, char delimiter);
    void add_curve_bezier(float precision);
    void relocation_pixel(vector <QPointF *> pixels);
    double distance(QPointF *a,QPointF *b);
    int where_pixel(vector<QPointF *> *group,QPointF *a);
    void draw_original_image();

};

#endif // MYGRAPHICSVIEW_H
