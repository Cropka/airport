#ifndef AIRPORT_H
#define AIRPORT_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "animationtimer.h"
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <vector>
#include "plane.h"
#include "resource.h"

//this class is a link from the backend to the GUI. GUI may take all of the coordinates and object types from here.
//(fields positionX, positionY, type from classes agent and resource)
class Airport : public QWidget
{
    Q_OBJECT
public:
    std::vector<Agent*> agents; //vector of all agents
    std::vector<Resource*> resources; //vector of all resources

    QGraphicsView* gui_object;
    QGraphicsItem *airport;

    QPixmap *airport_pic;

    QGraphicsScene *scene;

    int waypoint_y;
    //These parameters will be used for arriving to the first landing place
    int place_1_x;
    int place_1_y;
    int waypoint_1_x;
    int plane_1_ang;
    //These parameters will be used for arriving to the second landing place
    int place_2_x;
    int place_2_y;
    int waypoint_2_x;
    int plane_2_ang;
    //These parameters will be used for arriving to the third landing place
    int place_3_x;
    int place_3_y;
    int waypoint_3_x;
    int plane_3_ang;

    //These parameters will be used for arriving to the fourth landing place
    int place_4_x;
    int place_4_y;
    int waypoint_4_x;
    int plane_4_ang;

    int landing_runway_stop_y;
    int takeoff_runway_1_border_x;
    int takeoff_runway_2_border_x;

    AnimationTimer *clock1;
    AnimationTimer *clock2;
    AnimationTimer *clock3;
    AnimationTimer *clock4;
    AnimationTimer *clock5;
    AnimationTimer *clock6;
    AnimationTimer *clock7;
    AnimationTimer *clock8;

    AnimationTimer *landing_runway_1_clock;
    AnimationTimer *landing_runway_2_clock;

    AnimationTimer *docking_1_clock;
    AnimationTimer *docking_2_clock;
    AnimationTimer *docking_3_clock;
    AnimationTimer *docking_4_clock;

    AnimationTimer *takeoff_1_clock;
    AnimationTimer *takeoff_2_clock;
    AnimationTimer *takeoff_3_clock;
    AnimationTimer *takeoff_4_clock;
    AnimationTimer *resereve_takeoff_clock;


    explicit Airport(QWidget *parent = nullptr);
    ~Airport();
    int determine_spot(Agent *agent);
    void debugResources();
signals:
    void notifyNewAgentAdded(Agent*);
    void notifyNewResourceAdded(Resource*);
    void requestDocking(Agent*, int);
    void docked(Agent*, int);
    void takeoffFinished(Agent*);

public slots:
    void addAgent(Agent*, int);
    void addResource(Resource*, int);

    //Arriving the first 2 places by frist runway
//    void animate_arrive_place_1(Agent*);
//    void animate_arrive_place_2(Agent*);
//    //Arriving the 3,4 places by second runway
//    void animate_arrive_place_3(Agent*);
//    void animate_arrive_place_4(Agent*);

//    void arrive_place_1(Agent*);
//    void arrive_place_2(Agent*);
//    void arrive_place_3(Agent*);
//    void arrive_place_4(Agent*);
//    void takeoff_place_1(Agent*);
//    void takeoff_place_2(Agent*);
//    void takeoff_place_3(Agent*);
//    void takeoff_place_4(Agent*);

    void arrive_landing_runway(Agent*, int);
    void dock(Agent*, int);
    void takeoff(Agent*, int);

private:
    int get_place_x(int) const;
    int get_place_y(int) const;
private slots:
    void animate_landing_runway_1(Agent*);
    void animate_landing_runway_2(Agent*);
    void animate_docking_onto_the_spot_1(Agent*);
    void animate_docking_onto_the_spot_2(Agent*);
    void animate_docking_onto_the_spot_3(Agent*);
    void animate_docking_onto_the_spot_4(Agent*);
    void animate_takeoff_place_1(Agent*);
    void animate_takeoff_place_2(Agent*);
    void animate_takeoff_place_3(Agent*);
    void animate_takeoff_place_4(Agent*);
};

#endif // AIRPORT_H
