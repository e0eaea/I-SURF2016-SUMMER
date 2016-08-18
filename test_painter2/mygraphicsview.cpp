#include "mygraphicsview.h"
#include "QDebug"
#include "QThread"
#include <iostream>
#include <sstream>
#include <QLabel>


MyGraphicsView::MyGraphicsView(QMainWindow *mv,QWidget *widget):QGraphicsView(widget)
{
    this->mv=mv;
    now_point=0;
    epsilon = 11.0;
    is_drawing=false;
    is_selecting=false;
    gbi=NULL;

    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,widget->rect().width(),widget->rect().height()-40);
    this->setScene(scene);
    this->setRenderHints(QPainter::Antialiasing);
    this->show();

}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(is_selecting)
    {
        unselect_items();
        this->select_item_at(event->pos());
    }

    else
    {

        if (event->buttons() & Qt::LeftButton & (now_point<4))
        {
            QPointF point=QPointF(event->pos().x(),event->pos().y());

            points[now_point++]=point;
        }

        else if(now_point>4)
            QGraphicsView::mousePressEvent(event); // for moving point!(it's available to point 2,3)

    }

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Custom view released";

    QGraphicsView::mouseReleaseEvent(event);

    drawLines();
    update();


}

int MyGraphicsView::getNow_point() const
{
    return now_point;
}

void MyGraphicsView::setNow_point(int value)
{
    now_point = value;
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

void MyGraphicsView::set_original_pixels(vector<QPointF *> *pixels)
{
    this->original_pixels= *pixels;
    draw_original_image();
}

void MyGraphicsView::check_measurement()
{
    Measurement m;

    double total=0;

    for(int i=0; i<(int)original_pixels.size(); i++)
    {
        double min=0;
        for(int j=0; j<(int)curves.size(); j++)
        {
            MyGraphicBezier *bgi=curves[j];

            double d=m.NearestPointOnCurve(*original_pixels[i],bgi->getBezier_curve()->getControls());

            if(min==0 | d<min)
                min=d;
        }

        total+=min;
    }

    double avg=total/original_pixels.size();

    QString avg_num;
    avg_num.sprintf("%.2f",avg);
    QLabel *label = mv->findChild<QLabel *>("avg_d_val");

    label->setText(avg_num);

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

            gbi=item;
            points_ellipse.clear();
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
            qDebug()<<"ㅂㄱ";
            gbi=NULL;
            //points_ellipse.clear();
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

        curve->update();
        gbi=NULL;
        points_ellipse.clear();
    }

}


void MyGraphicsView::new_drawing()
{
    now_point=0;
    scene->clear();
    curves.clear();
    points_ellipse.clear();
    group_pixels.clear();

    if((int)original_pixels.size()!=0)
        draw_original_image();

}

void MyGraphicsView::add_drawing()
{
    //qDebug()<<points_ellipse<<"  "<<now_point;
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

    //    double rad = 1;

    //    for(int i=0; i<(int)pixels.size(); i++)
    //    {
    //        // qDebug()<<pixels[i]->rx()<<"  "<<pixels[i]->ry();
    //        QGraphicsEllipseItem *item= new QGraphicsEllipseItem(QRect(pixels[i]->rx(),pixels[i]->ry(),rad,rad));
    //        scene->addItem(item);
    //    }
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

    if(now_point==5)  //transform
    {
        if(gbi!=NULL)
        {
            int num=gbi->getCurve_number()-1;
            float precision=gbi->getBezier_curve()->getPrecision();

            scene->removeItem(gbi->getBezier_curve());
            delete gbi;
            gbi= curves.at(num)=NULL;
            gbi = new MyGraphicBezier(points_ellipse,precision);
            gbi->setCurve_number(num+1);


            qDebug()<<"this2";
            curves.at(num)=gbi;
            scene->addItem(gbi->getBezier_curve());

            check_measurement();
        }

    }


    if(now_point==4)
    {
        add_curve_bezier(0.01f);
        now_point++;
    }

}

void MyGraphicsView::add_curve_bezier(float precision)
{
    is_drawing=false;
    gbi = new MyGraphicBezier(points_ellipse,precision);
    this->curves.push_back(gbi);
    //    qDebug() <<curves.size()<<"여기 숫자저장";
    //    qDebug()<<gbi->getBezier_curve()->getControls();
    gbi->setCurve_number(this->curves.size());
    scene->addItem(gbi->getBezier_curve());
}

void MyGraphicsView::relocation_pixel(vector<QPointF *> pixels)
{
    while(true)
    {
        vector <QPointF *> remain_pixels;
        int pixel_size=pixels.size();
        //        qDebug()<<"사이즈는: "<<pixel_size;

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

        for(int i=0; i<(int)pixels.size(); i++)
            if(pixel_group_usebit[i]==0) remain_pixels.push_back(pixels[i]);

        //        qDebug()<<"남은거"<<remain_pixels.size();

        pixels.clear();

        for(int i=0; i<(int)remain_pixels.size(); i++)
            pixels.push_back(remain_pixels[i]);
    }

    for(int i=0; i<(int)group_pixels.size(); i++)
    {
        //        qDebug()<<"check ";
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
                ->rx()()<<j<<"번째  :  "<<*tmp_g[j];
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

    QString cur_num;
    cur_num.sprintf("%d",(int)curves.size());
    QLabel *label = mv->findChild<QLabel *>("curves_val");

    label->setText(cur_num);

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
    for(int i=0; i<(int)g.size(); i++)
    {
        qDebug()<<i<<"번째  "<<g[i];
        if(a==g[i])
        { num=i;  qDebug()<<"same"<<i;

            if(i==(int)g.size()-1)
                num++;
        }

    }

    return num;

}

void MyGraphicsView::draw_original_image()
{

    double rad = 1;
    QPen pen;
    pen.setColor(Qt::lightGray);

    for(int i=0; i<(int)original_pixels.size(); i++)
        scene->addEllipse(QRect(original_pixels[i]->rx(),original_pixels[i]->ry(),rad,rad),pen,QBrush(Qt::SolidPattern));
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
