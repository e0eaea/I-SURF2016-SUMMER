#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    startPos = QPoint();
    endPos = QPoint();
    inDrawing = false;
    setMouseTracking(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
//    QLabel label;

//    QRect rect;
//    rect.translate(20,20);
//    label.setFrameRect(rect);
//    label.setText("Hello!");

    pen.setColor(Qt::black);
    pen.setWidth(4);
    p.setPen(pen);

    drawLines(&p);
}

void Dialog::mousePressEvent(QMouseEvent *event)
{


    if (event->buttons() & Qt::LeftButton)
    {
        if (!inDrawing)
        {
            startPos = event->pos();
        }
        else
        {
            endPos = event->pos();


           QLine line = QLine(startPos, event->pos());
           lines.append(line);
        }

        inDrawing = !inDrawing;
    }

}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (inDrawing)
    {
        endPos = event->pos();
        update();
    }
}

void Dialog::drawLines(QPainter *p)
{
    if (!startPos.isNull() && !endPos.isNull())
    {
         p->drawPoint(startPos);
          p->drawPoint(endPos);

       // p->drawLine(startPos, endPos);
    }

   // p->drawLines(lines);
}




