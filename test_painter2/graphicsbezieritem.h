#ifndef GRAPHICSBEZIERITEM_H
#define GRAPHICSBEZIERITEM_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPen>

class GraphicsBezierItem : public QGraphicsItem
{
public:
    static const float DEFAULT_PRECISION;

    explicit GraphicsBezierItem(QGraphicsItem *parent = 0);
    GraphicsBezierItem(const QPointF &c1, const QPointF &c2, QGraphicsItem *parent = 0);
    GraphicsBezierItem(const QPointF &c1, const QPointF &c2, float precision, QGraphicsItem *parent = 0);

    void addControl(const QPointF &c);
    void setControl(std::size_t num, const QPointF &c);
    void removeControl(std::size_t num);

    const std::vector<QPointF>& getControls() const;
    const std::vector<QPointF>& getCurve() const;

    float getPrecision() const;
    void setPrecision(float value);

    QPen getPen() const;
    void setPen(const QPen &value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float distance(QPointF p0,QPointF p1);
    float contains_point(QPointF p, float epsilon);
    void set_selected(bool selected);
    void update();


//protected:
//     void mousePressEvent(QGraphicsSceneMouseEvent *event);
//     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
    std::vector<QPointF> controls;
    QPainterPath* path;
    float precision;
    std::vector<QPointF> curve;
    QRectF rect;
    QPen pen;
    bool is_select;
    void updateRect();

    QPointF tCurve(std::vector<QPointF> points, float t);
};

#endif // GRAPHICSBEZIERITEM_H
