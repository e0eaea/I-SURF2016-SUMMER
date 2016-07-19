

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicbezier.h"
#include "mygraphicsview.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>

#define MAX 100000

using namespace std;

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


void MainWindow::on_actionSave_Image_triggered()
{
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    if (!fileName.isNull())
    {
        QPixmap pixMap = ui->centralWidget->grab();
        pixMap.save(fileName);
    }
}

void MainWindow::on_actionSave_file_triggered()
{

    std::vector<MyGraphicBezier*> curves=view->getCurves();

    char tmp_s[MAX];

    foreach (MyGraphicBezier* curve, curves){
        sprintf(tmp_s,"%s%.2f",tmp_s,curve->getBezier_curve()->getPrecision());

        foreach(Mypoint *p, curve->getPoints_ellipse())
            sprintf(tmp_s,"%s %.2f %.2f",tmp_s,p->rect().center().x(),p->rect().center().y());


        sprintf(tmp_s,"%s\n",tmp_s);
    }



    qDebug()<<tmp_s;


    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Text File"), QCoreApplication::applicationDirPath(), tr("Text Files (*.txt)"));
    if (fileName != "")
    {
        QFile file(QFileInfo(fileName).absoluteFilePath());
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out <<tmp_s;
            file.close();
        }
        else
        {
            //TODO: Error message
        }
    }





}
