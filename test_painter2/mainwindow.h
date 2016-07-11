#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
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

private slots:
    void on_actionNew_triggered();
    void on_actionSave_file_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPixmap image;
    QImage  *imageObject;
    GraphicsBezierItem *gbi;
    QPointF points[4];
    int now_point;
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *p);

    void mousePressEvent(QMouseEvent *event);

};


#endif // MAINWINDOW_H
