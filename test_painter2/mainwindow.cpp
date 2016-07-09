

#include "mainwindow.h"

#include "ui_mainwindow.h"

#include "controlitem.h"

#include "graphicsbezieritem.h"





MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),

    ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    now_point=0;


    scene=new QGraphicsScene();
    scene->setSceneRect(0, 0, 400, 400);



    QGraphicsView* view=new QGraphicsView(ui->centralWidget);
    view->setScene(scene);
    view->setRenderHints(QPainter::Antialiasing);
    view->show();


}



void MainWindow::paintEvent(QPaintEvent *event)

{
    QPainter p(this);
    drawLines(&p);
}



void MainWindow::mousePressEvent(QMouseEvent *event)

{

    if (event->buttons() & Qt::LeftButton)
    {
        if(now_point==4)
        { now_point=0; scene->clear();}

        QPointF point=QPointF(event->pos());

        points[now_point++]=point;
 }

    update();

}





void MainWindow::drawLines(QPainter *p)

{
    if(now_point>0)
    {
        QPointF pt=points[now_point-1];

        double rad = 1;
        scene->addEllipse(pt.x(), pt.y(), rad*3.0, rad*3.0, QPen(), QBrush(Qt::SolidPattern));

        qDebug()<<pt;

        QGraphicsTextItem * io = new QGraphicsTextItem;
        io->setPos(pt.x(),pt.y());

        QString s;
        s.sprintf("p %d",now_point);

        io->setPlainText(s);
        scene->addItem(io);
    }


    if(now_point==4)
    {
        gbi = new GraphicsBezierItem(points[0], points[1]);
        gbi->addControl(points[2]);
        gbi->addControl(points[3]);
        scene->addItem(gbi);

    }



}



MainWindow::~MainWindow()

{

    delete ui;

}







