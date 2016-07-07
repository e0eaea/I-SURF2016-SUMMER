#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    now_point=0;

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    p.setPen(pen);

    drawLines(&p);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton)
    {

        QPoint point=QPoint(event->pos());
        points[now_point++]=point;

        if(now_point>4)
           now_point=0;
    }

    update();
}


void MainWindow::drawLines(QPainter *p)
{

    for(int i=1; i<=now_point; i++)
    {
        QPoint point=points[i-1];
        p->drawPoint(point);

        qDebug()<<point;

        QRect rect;
        rect.setRect(point.x(),point.y(),20,20);
        QString s;
        s.sprintf("p%d",i);
        p->drawText(rect,s);

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
