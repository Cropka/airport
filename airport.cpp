#include "airport.h"
#include <QDebug>
#include <iostream>
#include <QtMath>

Airport::Airport(QWidget *parent) : QWidget(parent)
{
    gui_object = new QGraphicsView(this);
    airport_pic = new QPixmap(":/images/airport.png");
    scene = new QGraphicsScene(this);

    clock1 = new AnimationTimer(this);
    clock2 = new AnimationTimer(this);
    clock3 = new AnimationTimer(this);
    clock4 = new AnimationTimer(this);
    clock5 = new AnimationTimer(this);
    clock6 = new AnimationTimer(this);
    clock7 = new AnimationTimer(this);
    clock8 = new AnimationTimer(this);

    waypoint_y = 408;
    //These parameters will be used for arriving to the first landing place
    place_1_x = 467;
    place_1_y = 258;
    waypoint_1_x = 467;
    plane_1_ang = 0;
    //These parameters will be used for arriving to the second landing place
    place_2_x = 657;
    place_2_y = 291;
    waypoint_2_x = 657;
    plane_2_ang = 0;
    //These parameters will be used for arriving to the third landing place
    place_3_x = 899;
    place_3_y = 292;
    waypoint_3_x = 899;
    plane_3_ang = 0;

    //These parameters will be used for arriving to the fourth landing place
    place_4_x = 1091;
    place_4_y = 261;
    waypoint_4_x = 1091;
    plane_4_ang = 0;


    gui_object->setGeometry(20, 10, 1441, 891);
    //Adding items to scene and taking back the handles
    gui_object->setScene(scene);
    gui_object->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gui_object->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    airport =   scene->addPixmap(*airport_pic);

    //Dont change that part - leave it be
    airport->setPos(0,0);
    airport->setScale(1.5);

    connect(clock1, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_1(Agent*)));
    connect(clock2, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_2(Agent*)));
    connect(clock3, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_3(Agent*)));
    connect(clock4, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_4(Agent*)));
    connect(clock5, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_1(Agent*)));
    connect(clock6, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_2(Agent*)));
    connect(clock7, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_3(Agent*)));
    connect(clock8, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_4(Agent*)));

}

Airport::~Airport(){
    delete airport;

    delete airport_pic;
//    delete plane_pic;

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

void Airport::addAgent(Agent *agent, int place)
{
    int x = get_place_x(place);
    int y = get_place_y(place);
    agent->setPos(x, y);
    scene->addItem(agent);
    agents.push_back(agent);
    emit notifyNewAgentAdded(agent);
}

void Airport::addResource(Resource *resource, int place)
{
//    int x = get_place_x(place);
//    int y = get_place_y(place);
//    resource->setPos(x, y);
    resources.push_back(resource);
    emit notifyNewResourceAdded(resource);
}


void Airport::arrive_place_1(Agent* plane)
{
    plane->setPos(place_1_x, 1000);
    plane->resetTransform();
    if(!(this->clock1->isActive()))
    {
        this->clock1->start(plane, 10);
    }
}


void Airport::arrive_place_2(Agent* plane)
{
    plane->setPos(place_1_x, 1000);
    plane->resetTransform();
    if(!(this->clock2->isActive()))
    {
        this->clock2->start(plane, 10);
    }
}


void Airport::arrive_place_3(Agent* plane)
{
    plane->setPos(place_4_x, 1000);
    plane->resetTransform();
    if(!(this->clock3->isActive()))
    {
        this->clock3->start(plane, 10);
    }
}


void Airport::arrive_place_4(Agent* plane)
{
    plane->setPos(place_4_x, 1000);
    plane->resetTransform();
    if(!(this->clock4->isActive()))
    {
        this->clock4->start(plane, 10);
    }
}

void Airport::takeoff_place_1(Agent *plane)
{
    plane->setPos(place_1_x, place_1_y);
    plane->resetTransform();
    if(!(this->clock5->isActive()))
    {
        this->clock5->start(plane, 10);
    }
}

void Airport::takeoff_place_2(Agent *plane)
{
    plane->setPos(place_2_x, place_2_y);
    plane->resetTransform();
    if(!(this->clock6->isActive()))
    {
        this->clock6->start(plane, 10);
    }
}

void Airport::takeoff_place_3(Agent *plane)
{
    plane->setPos(place_3_x, place_3_y);
    plane->resetTransform();
    plane->rotation_tracker = 0;
    if(!(this->clock7->isActive()))
    {
        this->clock7->start(plane, 10);
    }
}

void Airport::takeoff_place_4(Agent *plane)
{
    plane->setPos(place_4_x, place_4_y);
    plane->resetTransform();
    if(!(this->clock8->isActive()))
    {
        this->clock8->start(plane, 10);
    }
}

int Airport::get_place_x(int place) const
{
    switch(place) {
    case 0:
        return place_1_x;
    case 1:
        return place_1_x;
    case 2:
        return place_2_x;
    case 3:
        return place_3_x;
    case 4:
        return place_4_x;
    case 5:
        return place_4_x;
    }
    return 0;
}

int Airport::get_place_y(int place) const
{
    switch(place) {
    case 0:
        return 1000;
    case 1:
        return place_1_y;
    case 2:
        return place_2_y;
    case 3:
        return place_3_y;
    case 4:
        return place_4_y;
    case 5:
        return 1000;
    }
    return 0;
}


void Airport::animate_arrive_place_1(Agent *plane)
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

void Airport::animate_arrive_place_2(Agent *p)
{
    QRectF plane_pic = p->boundingRect();
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
                t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                t.rotate(this->plane_1_ang + 1);
                t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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
                    t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                    t.rotate(this->plane_1_ang - 1);
                    t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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

void Airport::animate_arrive_place_3(Agent *p)
{
    QRectF plane_pic = p->boundingRect();
    QTransform t;
    if(p->pos().y() > this->waypoint_y)
    {
        p->setPos(p->pos().x(), p->pos().y() - 1);
    }
    else if(p->pos().y() <= this->waypoint_y)
    {

        if(p->rotation_tracker != -90 && p->pos().x() == this->place_4_x)
        {
                t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                t.rotate(--p->rotation_tracker);
                t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
                p->setTransform(t);
        }
        else if(p->rotation_tracker >= -90)
        {

            if(p->pos().x() > this->place_3_x)
            {
               p->setPos(p->pos().x() - 1, p->pos().y());
            }
            else if(p->pos().x() == this->place_3_x)
            {

                if(p->rotation_tracker < 0)
                {
                    t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                    t.rotate(++p->rotation_tracker);
                    t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
                    p->setTransform(t);
                }
                else if(p->rotation_tracker == 0)
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

void Airport::animate_arrive_place_4(Agent *plane)
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

void Airport::animate_takeoff_place_1(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    QTransform t;

    if(plane->pos().y() == this->place_1_y && this->plane_1_ang != -180)
    {
        t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t.rotate(this->plane_1_ang - 1);
        t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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
            t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t.rotate(this->plane_1_ang + 1);
            t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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

void Airport::animate_takeoff_place_2(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    qDebug() << this->plane_1_ang;

    if(plane->pos().y() == this->place_2_y && this->plane_1_ang != -180)
    {
        QTransform t1;
        t1.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t1.rotate(this->plane_1_ang - 1);
        t1.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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
            t2.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t2.rotate(this->plane_1_ang + 1);
            t2.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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

void Airport::animate_takeoff_place_3(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    QTransform t;

    if(plane->pos().y() == this->place_3_y && this->plane_1_ang != -180)
    {
        t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t.rotate(this->plane_1_ang - 1);
        t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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
            t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t.rotate(this->plane_1_ang + 1);
            t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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

void Airport::animate_takeoff_place_4(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    QTransform t;

    if(plane->pos().y() == this->place_4_y && this->plane_1_ang != -180)
    {
        t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t.rotate(this->plane_1_ang - 1);
        t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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
            t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t.rotate(this->plane_1_ang + 1);
            t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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

