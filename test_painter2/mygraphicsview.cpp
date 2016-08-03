#include "mygraphicsview.h"
#include "QDebug"
#include <iostream>
#include <sstream>
#include <string>

MyGraphicsView::MyGraphicsView(QWidget *widget):QGraphicsView(widget)
{
    qDebug()<<"this";
    now_point=0;
    epsilon = 11.0;
    is_drawing=true;
    is_selecting=false;

    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,widget->rect().width(),widget->rect().height()-40);
    this->setScene(scene);
    this->setRenderHints(QPainter::Antialiasing);
    this->show();
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton & (now_point<4))
    {
        QPointF point=QPointF(event->pos().x(),event->pos().y());

        points[now_point++]=point;
    }
    else if(now_point>4)
    {

        QGraphicsView::mousePressEvent(event); // for moving point!(it's available to point 2,3)

        if(is_selecting)  // selecting curve for modifying!
        {
            unselect_items();
            this->select_item_at(event->pos());
        }
    }


}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Custom view released";

    QGraphicsView::mouseReleaseEvent(event);

    if(gbi != NULL)
    {
        drawLines();
        update();

    }


}

QGraphicsScene *MyGraphicsView::getScene() const
{
    return scene;
}

std::vector<MyGraphicBezier *> MyGraphicsView::getCurves() const
{
    return curves;
}

bool MyGraphicsView::getIs_selecting() const
{
    return is_selecting;
}

void MyGraphicsView::setIs_selecting(bool value)
{
    is_selecting = value;
}

bool MyGraphicsView::getIs_drawing() const
{
    return is_drawing;
}

void MyGraphicsView::select_item_at(QPoint p)
{


    QPointF point = this->mapToScene(p);
    this->unselect_items();

    foreach (MyGraphicBezier* item,curves)
    {
        GraphicsBezierItem*curve= item->getBezier_curve();
        if(curve->contains_point(point, this->epsilon))
        {
            qDebug()<<item->getCurve_number()<<"여기 확인";

            gbi=item;
            points_ellipse= item->getPoints_ellipse();
            curve->set_selected(true);

            for(int i=0; i<4; i++)
            {

                scene->addItem(points_ellipse.at(i));
                scene->addItem(points_ellipse.at(i)->getLabel());
            }
            curve->update();
            break;
        }

        else
        {
            qDebug()<<item->getCurve_number()<<"빈곳클릭";
            gbi=NULL;
            points_ellipse.clear();
        }

    }

}

void MyGraphicsView::unselect_items()
{
    if(gbi!=NULL)
    {
        GraphicsBezierItem*curve= gbi->getBezier_curve();
        curve->set_selected(false);
        points_ellipse= gbi->getPoints_ellipse();

        for(int i=0; i<4; i++)
        {
            scene->removeItem(points_ellipse.at(i));
            scene->removeItem(points_ellipse.at(i)->getLabel());

        }

        qDebug()<<"unselect"<<gbi->getCurve_number();
        curve->update();
        gbi=NULL;
        points_ellipse.clear();
    }

}


void MyGraphicsView::new_drawing()
{
    now_point=0; scene->clear();
    curves.clear();
    points_ellipse.clear();
    is_drawing=true;
}

void MyGraphicsView::add_drawing()
{
    qDebug()<<points_ellipse<<"  "<<now_point;
    clear_points_label();
    now_point=0;
    points_ellipse.clear();
}

void MyGraphicsView::add_curve(QString string)
{
    add_drawing();
    vector<double> s=split(string,' ');
    double rad = 1;
    points_ellipse.clear();
    for(int i=1; i<=4; i++)
    {
        Mypoint *mp=new Mypoint(i,QRect(s[2*i-1],s[2*i], rad, rad));
        points_ellipse.push_back(mp);
        scene->addItem(mp);
        scene->addItem(mp->getLabel());
    }

    add_curve_bezier(s[0]);
    now_point=5;

}

void MyGraphicsView::convert_image_to_point(vector<QPoint*> pixels)
{
    double rad = 1;

    for(int i=0; i<pixels.size(); i++)
     {
       // qDebug()<<pixels[i]->rx()<<"  "<<pixels[i]->ry();
        QGraphicsEllipseItem *item= new QGraphicsEllipseItem(QRect(pixels[i]->rx(),pixels[i]->ry(),rad,rad));
        scene->addItem(item);
    }

}



void MyGraphicsView::clear_points_label()
{
    for(int i=0; i<now_point-1; i++)
    {
        Mypoint* point=points_ellipse.at(i);
        scene->removeItem(point->getLabel());
        scene->removeItem(point);

    }
}

void MyGraphicsView::draw_points_label(int num)
{
    MyGraphicBezier* curve=curves.at(num);

    for(int i=0; i<4; i++)
    {
        Mypoint* point=curve->getPoints_ellipse().at(i);
        scene->addItem(point->getLabel());
        scene->addItem(point);
    }

}



void MyGraphicsView::drawLines()
{

    if(now_point>0 && now_point<=4)
    {
        QPointF pt=points[now_point-1];
        double rad = 1;
        Mypoint *mp=new Mypoint(now_point,QRect(pt.rx(),pt.ry(), rad, rad));
        scene->addItem(mp);
        scene->addItem(mp->getLabel());
        // qDebug()<<mp->rect().topRight()<<"    "<<mp->rect().topLeft();
        points_ellipse.push_back(mp);

        //qDebug()<<pt;
    }

    if(now_point==5)
    {

        int num=gbi->getCurve_number()-1;
        float precision=gbi->getBezier_curve()->getPrecision();
        qDebug()<<"출력샘플";


        scene->removeItem(gbi->getBezier_curve());
        delete gbi;
        qDebug()<<points_ellipse;
        gbi= curves.at(num)=NULL;
        gbi = new MyGraphicBezier(points_ellipse,precision);
        gbi->setCurve_number(num+1);
        curves.at(num)=gbi;
        scene->addItem(gbi->getBezier_curve());

        qDebug()<<"this";
        qDebug()<<curves.size();

        //여기서 지우고 업데이트
        //        gbi = new MyGraphicBezier(points_ellipse);
        //        this->curves.push_back(gbi);
        //    gbi->setCurve_number(this->curves.size());
        //
        // now_point++;
    }


    if(now_point==4)
    {

        add_curve_bezier(0.01f);
        qDebug() <<"여기"<<curves;
        now_point++;
    }

}

void MyGraphicsView::add_curve_bezier(float precision)
{
    is_drawing=false;
    gbi = new MyGraphicBezier(points_ellipse,precision);
    this->curves.push_back(gbi);
    qDebug() <<curves.size()<<"여기 숫자저장";
    qDebug()<<gbi->getBezier_curve()->getControls();
    gbi->setCurve_number(this->curves.size());
    scene->addItem(gbi->getBezier_curve());
}

vector<double> MyGraphicsView::split(QString str, char delimiter)
{
    vector<double> internal;
    stringstream ss(str.toStdString()); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(stof(tok));
        cout<<tok<<endl;
    }

    return internal;
}
