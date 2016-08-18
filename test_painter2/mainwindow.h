#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsView>
#include "mygraphicsview.h"
#include "mygraphicbezier.h"
#include "graphicsbezieritem.h"

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionSave_file_triggered();
    void on_actionAdd_curve_triggered();
    void on_actionModify_triggered();
    void change_enable_button();
    void on_actionSave_Image_triggered();

    void on_actionOpen_file_triggered();

    void on_actionOpen_image_triggered();

    void on_pushButton_clicked();

    void on_actionImport_Original_Image_triggered();

    void on_actionF_triggered();

private:
    bool modifying;
    bool exist_original;
    Ui::MainWindow *ui;
    MyGraphicsView* view;
    vector<QPointF*> pixels;
    vector<QPointF*> original_pixels;

};


#endif // MAINWINDOW_H
