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

    landing_runway_1_clock = new AnimationTimer(this);
    landing_runway_2_clock = new AnimationTimer(this);

    docking_1_clock = new AnimationTimer(this);
    docking_2_clock = new AnimationTimer(this);
    docking_3_clock = new AnimationTimer(this);
    docking_4_clock = new AnimationTimer(this);

    takeoff_1_clock = new AnimationTimer(this);
    takeoff_2_clock = new AnimationTimer(this);
    takeoff_3_clock = new AnimationTimer(this);
    takeoff_4_clock = new AnimationTimer(this);

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

    landing_runway_stop_y = waypoint_y + 100;
    takeoff_runway_1_border_x = place_1_x - 200;
    takeoff_runway_2_border_x = (place_3_x + place_2_x) / 2;

    gui_object->setGeometry(20, 10, 1441, 891);
    //Adding items to scene and taking back the handles
    gui_object->setScene(scene);
    gui_object->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gui_object->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    airport =   scene->addPixmap(*airport_pic);

    //Dont change that part - leave it be
    airport->setPos(0,0);
    airport->setScale(1.5);

//    connect(clock1, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_1(Agent*)));
//    connect(clock2, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_2(Agent*)));
//    connect(clock3, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_3(Agent*)));
//    connect(clock4, SIGNAL(nextStep(Agent*)), this, SLOT(animate_arrive_place_4(Agent*)));
//    connect(clock5, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_1(Agent*)));
//    connect(clock6, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_2(Agent*)));
//    connect(clock7, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_3(Agent*)));
//    connect(clock8, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_4(Agent*)));

    connect(landing_runway_1_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_landing_runway_1(Agent*)));
    connect(landing_runway_2_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_landing_runway_2(Agent*)));
    connect(docking_1_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_docking_onto_the_spot_1(Agent*)));
    connect(docking_2_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_docking_onto_the_spot_2(Agent*)));
    connect(docking_3_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_docking_onto_the_spot_3(Agent*)));
    connect(docking_4_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_docking_onto_the_spot_4(Agent*)));
    connect(takeoff_1_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_1(Agent*)));
    connect(takeoff_2_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_2(Agent*)));
    connect(takeoff_3_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_3(Agent*)));
    connect(takeoff_4_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_4(Agent*)));

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

int Airport::determine_spot(Agent *agent)
{
    int pos_x = agent->pos().x();
    for (int i=1; i<5; i++) {
        if (pos_x == get_place_x(i)) {
            return i;
        }
    }
    return 0;
}

void Airport::debugResources()
{
    std::cerr << "*******************************************" << std::endl;
    for (auto res : resources) {
        if (!res->isBusy()) {
            std::cerr << "Found free resource! : " << res->type() << " " << res->id << std::endl;
        }
    }
    std::cerr << "*******************************************" << std::endl;
}

void Airport::addAgent(Agent *agent, int place)
{
    if (place > 0 && place < 5) {
        agent->state = "landed";
        for (auto res : resources) {
            if (res->type() == "landing spot" && res->id == place) {
                res->markTaken();
            }
        }
    }
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


//void Airport::arrive_place_1(Agent* plane)
//{
//    plane->setPos(place_1_x, 1000);
//    plane->resetTransform();
//    if(!(this->clock1->isActive()))
//    {
//        this->clock1->start(plane, 10);
//    }
//}


//void Airport::arrive_place_2(Agent* plane)
//{
//    plane->setPos(place_1_x, 1000);
//    plane->resetTransform();
//    if(!(this->clock2->isActive()))
//    {
//        this->clock2->start(plane, 10);
//    }
//}


//void Airport::arrive_place_3(Agent* plane)
//{
//    plane->setPos(place_4_x, 1000);
//    plane->resetTransform();
//    if(!(this->clock3->isActive()))
//    {
//        this->clock3->start(plane, 10);
//    }
//}


//void Airport::arrive_place_4(Agent* plane)
//{
//    plane->setPos(place_4_x, 1000);
//    plane->resetTransform();
//    if(!(this->clock4->isActive()))
//    {
//        this->clock4->start(plane, 10);
//    }
//}

//void Airport::takeoff_place_1(Agent *plane)
//{
//    plane->setPos(place_1_x, place_1_y);
//    plane->resetTransform();
//    if(!(this->clock5->isActive()))
//    {
//        this->clock5->start(plane, 10);
//    }
//}

//void Airport::takeoff_place_2(Agent *plane)
//{
//    plane->setPos(place_2_x, place_2_y);
//    plane->resetTransform();
//    if(!(this->clock6->isActive()))
//    {
//        this->clock6->start(plane, 10);
//    }
//}

//void Airport::takeoff_place_3(Agent *plane)
//{
//    plane->setPos(place_3_x, place_3_y);
//    plane->resetTransform();
//    plane->rotation_tracker = 0;
//    if(!(this->clock7->isActive()))
//    {
//        this->clock7->start(plane, 10);
//    }
//}

//void Airport::takeoff_place_4(Agent *plane)
//{
//    plane->setPos(place_4_x, place_4_y);
//    plane->resetTransform();
//    if(!(this->clock8->isActive()))
//    {
//        this->clock8->start(plane, 10);
//    }
//}

void Airport::arrive_landing_runway(Agent *plane, int runway)
{
    plane->resetTransform();
    plane->rotation_tracker = 0;
    switch(runway) {
    case 1:
        plane->setPos(place_1_x, 1000);
        if(!(this->landing_runway_1_clock->isActive()))
        {
            this->landing_runway_1_clock->start(plane, 10);
        }
        break;
    case 2:
        plane->setPos(place_4_x, 1000);
        if(!(this->landing_runway_2_clock->isActive()))
        {
            this->landing_runway_2_clock->start(plane, 10);
        }
        break;
    }
}

void Airport::dock(Agent *plane, int place)
{
    plane->resetTransform();
    plane->rotation_tracker = 0;
    switch(place) {
    case 1:
        if(!(this->docking_1_clock->isActive()))
        {
            this->docking_1_clock->start(plane, 10);
        }
        break;
    case 2:
        if(!(this->docking_2_clock->isActive()))
        {
            this->docking_2_clock->start(plane, 10);
        }
        break;
    case 3:
        if(!(this->docking_3_clock->isActive()))
        {
            this->docking_3_clock->start(plane, 10);
        }
        break;
    case 4:
        if(!(this->docking_4_clock->isActive()))
        {
            this->docking_4_clock->start(plane, 10);
        }
        break;
    }
}

void Airport::takeoff(Agent *plane, int place)
{
    plane->resetTransform();
    plane->rotation_tracker = 0;
    switch(place) {
    case 1:
        if(!(this->takeoff_1_clock->isActive()))
        {
            this->takeoff_1_clock->start(plane, 10);
        } else {
            disconnect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), 0, 0);
            resereve_takeoff_clock = new AnimationTimer(this);
            connect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_1(Agent*)));
            resereve_takeoff_clock->start(plane, 10);
        }
        break;
    case 2:
        if(!(this->takeoff_2_clock->isActive()))
        {
            this->takeoff_2_clock->start(plane, 10);
        } else {
            disconnect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), 0, 0);
            resereve_takeoff_clock = new AnimationTimer(this);
            connect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_2(Agent*)));
            resereve_takeoff_clock->start(plane, 10);
        }
        break;
    case 3:
        if(!(this->takeoff_3_clock->isActive()))
        {
            this->takeoff_3_clock->start(plane, 10);
        } else {
            disconnect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), 0, 0);
            resereve_takeoff_clock = new AnimationTimer(this);
            connect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_3(Agent*)));
            resereve_takeoff_clock->start(plane, 10);
        }
        break;
    case 4:
        if(!(this->takeoff_4_clock->isActive()))
        {
            this->takeoff_4_clock->start(plane, 10);
        } else {
            disconnect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), 0, 0);
            resereve_takeoff_clock = new AnimationTimer(this);
            connect(resereve_takeoff_clock, SIGNAL(nextStep(Agent*)), this, SLOT(animate_takeoff_place_4(Agent*)));
            resereve_takeoff_clock->start(plane, 10);
        }
        break;
    }
    for (auto res : resources) {
        if (res->type() == "landing spot" && res->id == place) {
            res->markFree();
        }
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

void Airport::animate_landing_runway_1(Agent *plane)
{
    if(plane->pos().y() > this->landing_runway_stop_y)
    {
        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
    }
    else if(plane->pos().y() == this->landing_runway_stop_y)
    {
        this->landing_runway_1_clock->stop();
        emit requestDocking(plane, 1);
    }
}

void Airport::animate_landing_runway_2(Agent *plane)
{
    if(plane->pos().y() > this->landing_runway_stop_y)
    {
        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
    }
    else if(plane->pos().y() == this->landing_runway_stop_y)
    {
        this->landing_runway_2_clock->stop();
        emit requestDocking(plane, 2);
    }
}

void Airport::animate_docking_onto_the_spot_1(Agent *plane)
{
    if(plane->pos().y() > this->place_1_y)
    {
        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
    }
    else if(plane->pos().y() == this->place_1_y)
    {
        this->docking_1_clock->stop();
        emit docked(plane, 1);
    }
}

void Airport::animate_docking_onto_the_spot_2(Agent *p)
{
    QRectF plane_pic = p->boundingRect();
    QTransform t;
    if(p->pos().y() > this->waypoint_y)
    {
        p->setPos(p->pos().x(), p->pos().y() - 1);
    }
    else if(p->pos().y() <= this->waypoint_y)
    {

        if(p->rotation_tracker != 90 && p->pos().x() == this->place_1_x)
        {
                t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                t.rotate(p->rotation_tracker + 1);
                t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
                p->setTransform(t);
                p->rotation_tracker += 1;
        }
        else if(p->rotation_tracker <= 90)
        {

            if(p->pos().x() < this->place_2_x)
            {
               p->setPos(p->pos().x() + 1, p->pos().y());
            }
            else if(p->pos().x() == this->place_2_x)
            {

                if(p->rotation_tracker > 0)
                {
                    t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
                    t.rotate(p->rotation_tracker - 1);
                    t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
                    p->setTransform(t);

                    p->rotation_tracker -= 1;
                }
                else if(p->rotation_tracker == 0)
                {
                    if(p->pos().y() > this->place_2_y)
                    {
                        p->setPos(p->pos().x(), p->pos().y() - 1);
                    }
                    else if(p->pos().y() == this->place_2_y)
                    {
                       this->docking_2_clock->stop();
                       emit docked(p, 2);
                    }
                }
            }
        }
    }
}

void Airport::animate_docking_onto_the_spot_3(Agent *p)
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
                       this->docking_3_clock->stop();
                       emit docked(p, 3);
                    }
                }
            }
        }
    }
}

void Airport::animate_docking_onto_the_spot_4(Agent *plane)
{
    if(plane->pos().y() > this->place_4_y)
    {
        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
    }
    else if(plane->pos().y() == this->place_4_y)
    {
        this->docking_4_clock->stop();
        emit docked(plane, 4);
    }
}


//void Airport::animate_arrive_place_1(Agent *plane)
//{
//    if(plane->pos().y() > this->place_1_y)
//    {
//        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
//    }
//    else if(plane->pos().y() == this->place_1_y)
//    {
//        this->clock1->stop();
//    }
//}

//void Airport::animate_arrive_place_2(Agent *p)
//{
//    QRectF plane_pic = p->boundingRect();
//    QTransform t;
//    if(p->pos().y() > this->waypoint_y)
//    {
//        p->setPos(p->pos().x(), p->pos().y() - 1);
//    }
//    else if(p->pos().y() <= this->waypoint_y)
//    {

//        if(this->plane_1_ang != 90 && p->pos().x() == this->place_1_x)
//        {
//                t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
//                t.rotate(this->plane_1_ang + 1);
//                t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
//                p->setTransform(t);
//                this->plane_1_ang += 1;
//        }
//        else if(this->plane_1_ang <= 90)
//        {

//            if(p->pos().x() < this->place_2_x)
//            {
//               p->setPos(p->pos().x() + 1, p->pos().y());
//            }
//            else if(p->pos().x() == this->place_2_x)
//            {

//                if(this->plane_1_ang > 0)
//                {
//                    t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
//                    t.rotate(this->plane_1_ang - 1);
//                    t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
//                    p->setTransform(t);

//                    this->plane_1_ang -= 1;
//                }
//                else if(this->plane_1_ang == 0)
//                {
//                    if(p->pos().y() > this->place_2_y)
//                    {
//                        p->setPos(p->pos().x(), p->pos().y() - 1);
//                    }
//                    else if(p->pos().y() == this->place_2_y)
//                    {
//                       this->clock2->stop();
//                    }
//                }
//            }
//        }
//    }
//}

//void Airport::animate_arrive_place_3(Agent *p)
//{
//    QRectF plane_pic = p->boundingRect();
//    QTransform t;
//    if(p->pos().y() > this->waypoint_y)
//    {
//        p->setPos(p->pos().x(), p->pos().y() - 1);
//    }
//    else if(p->pos().y() <= this->waypoint_y)
//    {

//        if(p->rotation_tracker != -90 && p->pos().x() == this->place_4_x)
//        {
//                t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
//                t.rotate(--p->rotation_tracker);
//                t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
//                p->setTransform(t);
//        }
//        else if(p->rotation_tracker >= -90)
//        {

//            if(p->pos().x() > this->place_3_x)
//            {
//               p->setPos(p->pos().x() - 1, p->pos().y());
//            }
//            else if(p->pos().x() == this->place_3_x)
//            {

//                if(p->rotation_tracker < 0)
//                {
//                    t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
//                    t.rotate(++p->rotation_tracker);
//                    t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
//                    p->setTransform(t);
//                }
//                else if(p->rotation_tracker == 0)
//                {
//                    if(p->pos().y() > this->place_3_y)
//                    {
//                        p->setPos(p->pos().x(), p->pos().y() - 1);
//                    }
//                    else if(p->pos().y() == this->place_3_y)
//                    {
//                       this->clock3->stop();

//                    }
//                }
//            }
//        }
//    }
//}

//void Airport::animate_arrive_place_4(Agent *plane)
//{
//    if(plane->pos().y() > this->place_4_y)
//    {
//        plane->setPos(plane->pos().x(), plane->pos().y() - 1);
//    }
//    else if(plane->pos().y() == this->place_4_y)
//    {
//        this->clock4->stop();
//    }
//}

void Airport::animate_takeoff_place_1(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    QTransform t;

    if(plane->pos().y() == this->place_1_y && plane->rotation_tracker != -180)
    {
        t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t.rotate(plane->rotation_tracker - 1);
        t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
        plane->setTransform(t);
        plane->rotation_tracker -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && plane->rotation_tracker != -90)
        {
            t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t.rotate(plane->rotation_tracker + 1);
            t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
            plane->setTransform(t);
            plane->rotation_tracker += 1;
        }
        else if(plane->rotation_tracker == -90)
        {
            if(plane->pos().x() != -100) {
                plane->setPos(plane->pos().x() - 1, plane->pos().y());
                if (plane->pos().x() == takeoff_runway_1_border_x) {
                    for (auto res : resources) {
                        if (res->type() == "takeoff runway" && res->id == 1)
                            res->markFree();
                    }
                }
            } else {
                this->takeoff_1_clock->stop();
                emit takeoffFinished(plane);
            }
        }
    }
}

void Airport::animate_takeoff_place_2(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();

    if(plane->pos().y() == this->place_2_y && plane->rotation_tracker != -180)
    {
        QTransform t1;
        t1.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t1.rotate(plane->rotation_tracker - 1);
        t1.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
        plane->setTransform(t1);
        plane->rotation_tracker -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && plane->rotation_tracker != -90)
        {
            QTransform t2;
            t2.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t2.rotate(plane->rotation_tracker + 1);
            t2.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
            plane->setTransform(t2);
            plane->rotation_tracker += 1;
        }
        else if(plane->rotation_tracker == -90)
        {
            if(plane->pos().x() != -100) {
                plane->setPos(plane->pos().x() - 1, plane->pos().y());
                if (plane->pos().x() == takeoff_runway_1_border_x) {
                    for (auto res : resources) {
                        if (res->type() == "takeoff runway" && res->id == 1)
                            res->markFree();
                    }
                }
            } else {
                this->takeoff_2_clock->stop();
                emit takeoffFinished(plane);
            }
        }
    }
}

void Airport::animate_takeoff_place_3(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    QTransform t;

    if(plane->pos().y() == this->place_3_y && plane->rotation_tracker != -180)
    {
        t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t.rotate(plane->rotation_tracker - 1);
        t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
        plane->setTransform(t);
        plane->rotation_tracker -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && plane->rotation_tracker != -90)
        {
            t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t.rotate(plane->rotation_tracker + 1);
            t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
            plane->setTransform(t);
            plane->rotation_tracker += 1;
        }
        else if(plane->rotation_tracker == -90)
        {
            if(plane->pos().x() != -100) {
                plane->setPos(plane->pos().x() - 1, plane->pos().y());
                if (plane->pos().x() == takeoff_runway_2_border_x) {
                    for (auto res : resources) {
                        if (res->type() == "takeoff runway" && res->id == 2)
                            res->markFree();
                    }
                }
                if (plane->pos().x() == takeoff_runway_1_border_x) {
                    for (auto res : resources) {
                        if (res->type() == "takeoff runway" && res->id == 1)
                            res->markFree();
                    }
                }
            } else {
                this->takeoff_3_clock->stop();
                emit takeoffFinished(plane);
            }
        }
    }
}

void Airport::animate_takeoff_place_4(Agent *plane)
{
    QRectF plane_pic = plane->boundingRect();
    QTransform t;

    if(plane->pos().y() == this->place_4_y && plane->rotation_tracker != -180)
    {
        t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
        t.rotate(plane->rotation_tracker - 1);
        t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
        plane->setTransform(t);
        plane->rotation_tracker -= 1;
    }
    else
    {
        if(plane->pos().y() != this->waypoint_y)
        {
            plane->setPos(plane->pos().x(), plane->pos().y() + 1);
        }
        else if(plane->pos().y() == this->waypoint_y && plane->rotation_tracker != -90)
        {
            t.translate((plane_pic.width()*0.025)/2, (plane_pic.height()*0.025)/2);
            t.rotate(plane->rotation_tracker + 1);
            t.translate(-((plane_pic.width()*0.025)/2), -((plane_pic.height()*0.025)/2));
            plane->setTransform(t);
            plane->rotation_tracker += 1;
        }
        else if(plane->rotation_tracker == -90)
        {
            if(plane->pos().x() != -100) {
                plane->setPos(plane->pos().x() - 1, plane->pos().y());
                if (plane->pos().x() < takeoff_runway_2_border_x) {
                    for (auto res : resources) {
                        if (res->type() == "takeoff runway" && res->id == 2)
                            res->markFree();
                    }
                }
                if (plane->pos().x() == takeoff_runway_1_border_x) {
                    for (auto res : resources) {
                        if (res->type() == "takeoff runway" && res->id == 1)
                            res->markFree();
                    }
                }
            } else {
                this->takeoff_4_clock->stop();
                emit takeoffFinished(plane);
            }
        }
    }
}


