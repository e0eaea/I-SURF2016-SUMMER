

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicbezier.h"
#include "mygraphicsview.h"
#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view=new MyGraphicsView(ui->centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
   view->new_drawing();
}

void MainWindow::on_actionSave_file_triggered()
{
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    if (!fileName.isNull())
    {
        QPixmap pixMap = ui->centralWidget->grab();
        pixMap.save(fileName);
    }
}
