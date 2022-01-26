#include "airport.h"
#include <QDebug>

Airport::Airport(QWidget *parent) : QWidget(parent)
{
    gui_object->setGeometry(20, 10, 1441, 891);
    //Adding items to scene and taking back the handles
    gui_object->setScene(scene);
    gui_object->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gui_object->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    airport =   scene->addPixmap(*airport_pic);

    //Dont change that part - leave it be
    airport->setPos(0,0);
    airport->setScale(1.5);

    //connect(clock1, SIGNAL(timeout()), this, SLOT(arrive_place_1()));

    //connect(ui->arrive2, SIGNAL(clicked()), this, SLOT(move_to_second()));

    connect(clock2, SIGNAL(timeout()), this, SLOT(arrive_place_2()));
    connect(clock1, SIGNAL(timeout()), this, SLOT(move_to_second()));

    connect(this, SIGNAL(trigger_arrive_2(QGraphicsItem*)), this, SLOT(animate_arrive_place_2(QGraphicsItem*)));
    connect(this, SIGNAL(trigger_takeoff_2(QGraphicsItem*)), this, SLOT(animate_takeoff_place_2(QGraphicsItem*)));

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
    if(!(this->clock1->isActive()))
    {
        plane->setPos(place_1_x, 1000);
        this->clock1->start(10);
    }

    animate_arrive_place_1(plane);
}


void Airport::arrive_place_2(Agent* plane)
{
    if(!(this->clock2->isActive()))
    {
        this->clock2->start(10);
    }

    emit trigger_arrive_2(plane);
}


void Airport::arrive_place_3(Agent* plane)
{
    if(!(this->clock3->isActive()))
    {
        plane->setPos(place_4_x, 1000);
        this->clock3->start(10);
    }

    animate_arrive_place_3(plane);
}


void Airport::arrive_place_4(Agent* plane)
{
    if(!(this->clock4->isActive()))
    {
        plane->setPos(place_4_x, 1000);
        this->clock4->start(10);
    }

    animate_arrive_place_4(plane);
}

void Airport::takeoff_place_1(Agent *plane)
{

}

void Airport::takeoff_place_2(Agent *plane)
{

}

void Airport::takeoff_place_3(Agent *plane)
{

}

void Airport::takeoff_place_4(Agent *plane)
{

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


void Airport::animate_arrive_place_1(QGraphicsItem *plane)
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

void Airport::animate_arrive_place_2(QGraphicsItem *p)
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

void Airport::animate_arrive_place_3(QGraphicsItem *p)
{
    QRectF plane_pic = p->boundingRect();
    QTransform t;
    if(p->pos().y() > this->waypoint_y)
    {
        p->setPos(p->pos().x(), p->pos().y() - 1);
    }
    else if(p->pos().y() <= this->waypoint_y)
    {

        if(this->plane_1_ang != -90 && p->pos().x() == this->place_3_x)
        {
                t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                t.rotate(this->plane_1_ang - 1);
                t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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
                    t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                    t.rotate(this->plane_1_ang + 1);
                    t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
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

void Airport::animate_arrive_place_4(QGraphicsItem *plane)
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

void Airport::animate_takeoff_place_1(QGraphicsItem *plane)
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

void Airport::animate_takeoff_place_2(QGraphicsItem *plane)
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

void Airport::animate_takeoff_place_3(QGraphicsItem *plane)
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

void Airport::animate_takeoff_place_4(QGraphicsItem *plane)
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

