#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QLabel>

namespace Ui {
class Dialog;

}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *p);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);


    QPoint startPos;
    QPoint endPos;
    bool inDrawing;
    QVector<QLine> lines;
    QVector<QPoint> points;
};

#endif // DIALOG_H
