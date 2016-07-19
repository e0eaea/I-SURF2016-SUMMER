

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
    modifying=false;

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

void MainWindow::on_actionAdd_curve_triggered()
{
    qDebug()<<"add click";
    view->add_drawing();
}

void MainWindow::on_actionModify_triggered()
{
    qDebug()<<"modify click";

    if(!view->getIs_drawing())
    {
        if(!modifying)
         ui->actionModify->setText("Done");

        else
            ui->actionModify->setText("Modify");

        change_enable_button();
        modifying=!modifying;
        view->setIs_selecting(modifying);
    }


}

void MainWindow::change_enable_button()
{
    ui->actionNew->setEnabled(modifying);
    ui->actionAdd_curve->setEnabled(modifying);
    ui->actionSave_file->setEnabled(modifying);

}

