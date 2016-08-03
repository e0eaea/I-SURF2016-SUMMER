#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include<QtGui>

#include <QGraphicsScene>
#include "mygraphicbezier.h"

using namespace std;
class MyGraphicsView: public QGraphicsView
{
public:
    MyGraphicsView(QWidget *widget);
    void new_drawing();
    void add_drawing();
    void add_curve(QString string);
    void convert_image_to_point(vector <QPoint *> pixels);
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

    bool is_drawing;
    bool is_selecting;
    float epsilon;
    void drawLines();
    void select_item_at(QPoint p);
    void unselect_items();
    vector<double>split(QString str, char delimiter);
    void add_curve_bezier(float precision);

};

#endif // MYGRAPHICSVIEW_H
