#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "graphicsbezieritem.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    GraphicsBezierItem *gbi;
    QPointF points[4];
    int now_point;
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *p);

    void mousePressEvent(QMouseEvent *event);

};


#endif // MAINWINDOW_H
