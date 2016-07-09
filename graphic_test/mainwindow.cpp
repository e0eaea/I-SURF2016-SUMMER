#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene= new QGraphicsScene(this);
    scene->setSceneRect(50, 50, 350, 350);

    square=new Mysquare();
    scene->addItem(square);


    QGraphicsView* view = new QGraphicsView(scene);
    view->show();

}

MainWindow::~MainWindow()
{
}
