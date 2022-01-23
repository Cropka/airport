#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QTransform>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    gui_object->setGeometry(20, 10, 1441, 891);
    arrive1->setGeometry(1300, 850, 100,40);
    //Adding items to scene and taking back the handles
    gui_object->setScene(scene);
    gui_object->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gui_object->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    airport =   scene->addPixmap(*airport_pic);
    plane   =   scene->addPixmap(*plane_pic);
    plane1  =   scene->addPixmap(*plane_pic);
    plane2  =   scene->addPixmap(*plane_pic);
    plane3  =   scene->addPixmap(*plane_pic);

    //Dont change that part - leave it be
    airport->setPos(0,0);
    airport->setScale(1.5);
    //Dont change that part - leave it be

    plane->setPos(place_1_x, 1000);
    plane->setRotation(0);
    plane->setScale(0.025);

    plane1->setPos(place_1_x, 900);
    plane1->setRotation(0);
    plane1->setScale(0.025);

    plane2->setPos(place_3_x, place_3_y);
    plane2->setRotation(0);
    plane2->setScale(0.025);

    plane3->setPos(place_4_x, place_4_y);
    plane3->setRotation(0);
    plane3->setScale(0.025);


    //connect(clock1, SIGNAL(timeout()), this, SLOT(arrive_place_1()));

    connect(arrive1, SIGNAL(clicked()), this, SLOT(move1()));
    //connect(ui->arrive2, SIGNAL(clicked()), this, SLOT(move_to_second()));

    connect(clock1, SIGNAL(timeout()), this, SLOT(move1()));
    connect(clock2, SIGNAL(timeout()), this, SLOT(move_to_second()));

    connect(this, SIGNAL(set_up(QGraphicsItem*)), this, SLOT(arrive_place_2(QGraphicsItem*)));
    connect(this, SIGNAL(set_up1(QGraphicsItem*)), this, SLOT(takeoff_place_2(QGraphicsItem*)));


}

MainWindow::~MainWindow()
{

    delete plane;
    delete plane1;
    delete plane2;
    delete plane3;
    delete airport;

    delete airport_pic;
    delete plane_pic;

    delete scene;

    //Delete clock nedeed for Visualization
    delete clock1;
    delete clock2;
    delete clock3;
    delete clock4;
    delete clock5;
    delete clock6;
    delete clock7;
    delete clock8;
}

void MainWindow::move1()
{
    if(!(this->clock1->isActive()))
    {
        this->plane->setPos(place_1_x, 1000);
        this->clock1->start(10);
    }

    emit set_up(this->plane);
}

void MainWindow::move_to_second()
{
    if(!(this->clock2->isActive()))
    {
        this->clock2->start(10);
    }

    emit set_up1(this->plane1);
}

void MainWindow::arrive_place_1(QGraphicsItem *plane)
{
    if(plane->pos().y() > this->place_1_y)
    {
        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
    }
    else if(plane->pos().y() == this->place_1_y)
    {
        this->clock1->stop();
        qDebug() << "Plane 2 arrvied";
    }
}

void MainWindow::arrive_place_2(QGraphicsItem *p)
{

    QTransform t;
    qDebug() << this->plane_1_ang;
    qDebug() << p->rotation();
    if(p->pos().y() > this->waypoint_y)
    {
        p->setPos(p->pos().x(), p->pos().y() - 1);
    }
    else if(p->pos().y() <= this->waypoint_y)
    {

        if(this->plane_1_ang != 90 && p->pos().x() == this->place_1_x)
        {
                t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
                t.rotate(this->plane_1_ang + 1);
                t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
                p->setTransform(t);
                this->plane_1_ang += 1;
        }
        else if(this->plane_1_ang <= 90)
        {

            if(p->pos().x() < this->place_2_x)
            {
               p->setPos(p->pos().x() + 1, p->pos().y());
            }
            else if(p->pos().x() == this->place_2_x)
            {

                if(this->plane_1_ang > 0)
                {
                    t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
                    t.rotate(this->plane_1_ang - 1);
                    t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
                    p->setTransform(t);

                    this->plane_1_ang -= 1;
                }
                else if(this->plane_1_ang == 0)
                {
                    if(p->pos().y() > this->place_2_y)
                    {
                        p->setPos(p->pos().x(), p->pos().y() - 1);
                    }
                    else if(p->pos().y() == this->place_2_y)
                    {
                       this->clock2->stop();

                    }
                }
            }
        }
    }
}

void MainWindow::arrive_place_3(QGraphicsItem *p)
{

    QTransform t;
    if(p->pos().y() > this->waypoint_y)
    {
        p->setPos(p->pos().x(), p->pos().y() - 1);
    }
    else if(p->pos().y() <= this->waypoint_y)
    {

        if(this->plane_1_ang != -90 && p->pos().x() == this->place_3_x)
        {
                t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
                t.rotate(this->plane_1_ang - 1);
                t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
                p->setTransform(t);
                this->plane_1_ang -= 1;
        }
        else if(this->plane_1_ang >= -90)
        {

            if(p->pos().x() < this->place_3_x)
            {
               p->setPos(p->pos().x() - 1, p->pos().y());
            }
            else if(p->pos().x() == this->place_3_x)
            {

                if(this->plane_1_ang < 0)
                {
                    t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
                    t.rotate(this->plane_1_ang + 1);
                    t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
                    p->setTransform(t);

                    this->plane_1_ang += 1;
                }
                else if(this->plane_1_ang == 0)
                {
                    if(p->pos().y() > this->place_3_y)
                    {
                        p->setPos(p->pos().x(), p->pos().y() - 1);
                    }
                    else if(p->pos().y() == this->place_3_y)
                    {
                       this->clock3->stop();

                    }
                }
            }
        }
    }
}

void MainWindow::arrive_place_4(QGraphicsItem *plane)
{
    if(plane->pos().y() > this->place_4_y)
    {
        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
    }
    else if(plane->pos().y() == this->place_4_y)
    {
        this->clock4->stop();
        qDebug() << "Plane 2 arrvied";
    }
}

void MainWindow::takeoff_place_1(QGraphicsItem *plane)
{
    QTransform t;

    if(plane->pos().y() == this->place_1_y && this->plane_1_ang != -180)
    {
        t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
        t.rotate(this->plane_1_ang - 1);
        t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
        plane->setTransform(t);
        this->plane_1_ang -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && this->plane_1_ang != -90)
        {
            t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
            t.rotate(this->plane_1_ang + 1);
            t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
            plane->setTransform(t);
            this->plane_1_ang += 1;
        }
        else if(this->plane_1_ang == -90)
        {
            if(plane->pos().x() != -100)
            plane->setPos(plane->pos().x() - 1, plane->pos().y());
            else
            {
                this->clock5->stop();
                qDebug() << "Plane in the Air";
            }
        }
    }
}

void MainWindow::takeoff_place_2(QGraphicsItem *plane)
{
    qDebug() << this->plane_1_ang;

    if(plane->pos().y() == this->place_2_y && this->plane_1_ang != -180)
    {
        QTransform t1;
        t1.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
        t1.rotate(this->plane_1_ang - 1);
        t1.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
        plane->setTransform(t1);
        this->plane_1_ang -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && this->plane_1_ang != -90)
        {
            QTransform t2;
            t2.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
            t2.rotate(this->plane_1_ang + 1);
            t2.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
            plane->setTransform(t2);
            this->plane_1_ang += 1;
        }
        else if(this->plane_1_ang == -90)
        {
            if(plane->pos().x() != -100)
            plane->setPos(plane->pos().x() - 1, plane->pos().y());
            else
            {
            qDebug() << "Plane in the Air";
            this->clock6->stop();
            plane->setRotation(0);
            this->plane_1_ang = 0;
            }
        }
    }
}

void MainWindow::takeoff_place_3(QGraphicsItem *plane)
{
    QTransform t;

    if(plane->pos().y() == this->place_3_y && this->plane_1_ang != -180)
    {
        t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
        t.rotate(this->plane_1_ang - 1);
        t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
        plane->setTransform(t);
        this->plane_1_ang -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && this->plane_1_ang != -90)
        {
            t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
            t.rotate(this->plane_1_ang + 1);
            t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
            plane->setTransform(t);
            this->plane_1_ang += 1;
        }
        else if(this->plane_1_ang == -90)
        {
            if(plane->pos().x() != -100)
            plane->setPos(plane->pos().x() - 1, plane->pos().y());
            else
            {
                this->clock7->stop();
                qDebug() << "Plane in the Air";
            }
        }
    }
}

void MainWindow::takeoff_place_4(QGraphicsItem *plane)
{
    QTransform t;

    if(plane->pos().y() == this->place_4_y && this->plane_1_ang != -180)
    {
        t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
        t.rotate(this->plane_1_ang - 1);
        t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
        plane->setTransform(t);
        this->plane_1_ang -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && this->plane_1_ang != -90)
        {
            t.translate((plane_pic->width()*0.025)/2, (plane_pic->height()*0.025)/2);
            t.rotate(this->plane_1_ang + 1);
            t.translate(-((plane_pic->width()*0.025)/2), -((plane_pic->height()*0.025)/2));
            plane->setTransform(t);
            this->plane_1_ang += 1;
        }
        else if(this->plane_1_ang == -90)
        {
            if(plane->pos().x() != -100)
            plane->setPos(plane->pos().x() - 1, plane->pos().y());
            else
            {
                this->clock8->stop();
                qDebug() << "Plane in the Air";
            }
        }
    }
}
