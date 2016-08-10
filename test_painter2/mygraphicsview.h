#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include<QtGui>
#include <QGraphicsScene>
#include "mygraphicbezier.h"
#include "fitcurve.h"

using namespace std;
class MyGraphicsView: public QGraphicsView
{
public:
    MyGraphicsView(QWidget *widget);
    void new_drawing();
    void add_drawing();
    void add_curve(QString string);
    void convert_image_to_point(vector <QPointF *> pixels);
    void clear_points_label();
    void draw_points_label(int num);
    bool getIs_drawing() const;
    bool getIs_selecting() const;
    void setIs_selecting(bool value);
    vector<MyGraphicBezier *> getCurves() const;

    QGraphicsScene *getScene() const;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    MyGraphicBezier *gbi;
    std::vector<MyGraphicBezier*> curves;
    QGraphicsScene *scene;
    std::vector<Mypoint *> points_ellipse;
    QPointF points[4];
    int now_point;
    vector<QPointF*> group_pixels;

    bool is_drawing;
    bool is_selecting;
    float epsilon;
    void drawLines();
    void select_item_at(QPoint p);
    void unselect_items();
    vector<double>split(QString str, char delimiter);
    void add_curve_bezier(float precision);
    void relocation_pixel(vector <QPointF *> pixels);
    double distance(QPointF *a,QPointF *b);
    int where_pixel(vector<QPointF *> *group,QPointF *a);

};

#endif // MYGRAPHICSVIEW_H
