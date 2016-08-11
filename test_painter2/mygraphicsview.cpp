#include "mygraphicsview.h"
#include "QDebug"
#include "QThread"
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
    group_pixels.clear();

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
    double rad = 5;
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

void MyGraphicsView::convert_image_to_point(vector<QPointF *> pixels, int min_d, double fit_error, int iteration)
{
    new_drawing();

    double rad = 1;

    for(int i=0; i<(int)pixels.size(); i++)
    {
        // qDebug()<<pixels[i]->rx()<<"  "<<pixels[i]->ry();
        QGraphicsEllipseItem *item= new QGraphicsEllipseItem(QRect(pixels[i]->rx(),pixels[i]->ry(),rad,rad));
        scene->addItem(item);
    }
    // for(int i=1; i<(int)pixels.size(); i++)

    this->min_d=min_d;
    this->fit_error=fit_error;
    this->fit_iter=iteration;
    relocation_pixel(pixels);

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
        is_drawing=true;
        QPointF pt=points[now_point-1];
        double rad = 5;
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

void MyGraphicsView::relocation_pixel(vector<QPointF *> pixels)
{
    while(true)
    {
        vector <QPointF *> remain_pixels;
        int pixel_size=pixels.size();
        qDebug()<<"사이즈는: "<<pixel_size;

        if(pixel_size==0)
            break;

        int* pixel_group_usebit=new int[pixel_size];

        for(int i=1; i<pixel_size; i++)
            pixel_group_usebit[i]=0;

        vector <QPointF *> *g=new vector <QPointF *>;
        group_pixels.push_back(g);

        g->push_back(pixels[0]);
        pixel_group_usebit[0]=1;

        for(int i=1; i<(int)pixels.size(); i++)
        {

            double min=min_d;
            int last=g->size()-1;

            int neighbor=-1;
            for(int j=0; j<(int)pixels.size(); j++)
            {
                if(pixel_group_usebit[j]==0)
                {
                    double d=distance(g[0][last],pixels[j]);

                    if(min>d && d!=0)
                    {  min=d; neighbor=j;}
                }
            }

            if(neighbor==-1)
            {
                for(int j=1; j<(int)pixels.size(); j++)
                {
                    if(pixel_group_usebit[j]==0)
                    {
                        double d=distance(g[0][0],pixels[j]);

                        if(min>d)
                        {  min=d; neighbor=j;}
                    }
                }

                if(neighbor!=-1)
                {
                    vector<QPointF*>::iterator it_start=g->begin();
                    g->insert(it_start,pixels[neighbor]);
                    pixel_group_usebit[neighbor]=1;
                }

            }

            else{
                g->push_back(pixels[neighbor]);
                pixel_group_usebit[neighbor]=1;
            }
        }


        //copy remain to original

        for(int i=0; i<pixels.size(); i++)
            if(pixel_group_usebit[i]==0) remain_pixels.push_back(pixels[i]);

        qDebug()<<"남은거"<<remain_pixels.size();

        pixels.clear();

        for(int i=0; i<remain_pixels.size(); i++)
            pixels.push_back(remain_pixels[i]);
    }

    for(int i=0; i<group_pixels.size(); i++)
    {
        qDebug()<<"check ";
        vector <QPointF *> *gp=group_pixels[i];
        vector <QPointF *> tmp_g=*gp;

        vector<QPointF*>::iterator it_s=tmp_g.begin();
        vector<QPointF*>::iterator it_e=tmp_g.end()-1;

        if(distance(*it_s,*it_e)<min_d)
            tmp_g.push_back(tmp_g[0]);

        if(tmp_g.size()>=2)
        {
            /*
            for(int j=0; j<(int)tmp_g.size(); j++)
            {
                qDebug()<<j<<"번째  :  "<<*tmp_g[j];
                Mypoint *mp1=new Mypoint(j,QRect(tmp_g[j]->rx(),tmp_g[j]->ry(), 3, 3));
                scene->addItem(mp1);
                scene->addItem(mp1->getLabel());
            }
            */

            FitCurve fitcurve(tmp_g,fit_error,fit_iter);
            fitcurve.start_fit_curve();

            vector<MyGraphicBezier*> tmp_curves=fitcurve.getCurves();

            for(int k=0; k<(int)tmp_curves.size(); k++)
            {
                curves.push_back(tmp_curves[k]);
                tmp_curves[k]->setCurve_number(this->curves.size());
                scene->addItem(tmp_curves[k]->getBezier_curve());
            }
        }
    }






}

double MyGraphicsView::distance(QPointF *a, QPointF *b)
{
    double x=a->rx()- b->rx();
    double y=a->ry()- b->ry();

    return sqrt(x*x+y*y);

}

int MyGraphicsView::where_pixel(vector<QPointF *> *group,QPointF *a)
{
    int num;
    vector<QPointF *> g=*group;
    for(int i=0; i<g.size(); i++)
    {
        qDebug()<<i<<"번째  "<<g[i];
        if(a==g[i])
        { num=i;  qDebug()<<"same"<<i;

            if(i==g.size()-1)
                num++;
        }

    }

    return num;

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
