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
#include <QTimer>
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

    QGraphicsView* gui_object = new QGraphicsView(this);
    QGraphicsItem *airport;

    QPixmap *airport_pic = new QPixmap(":/images/airport.png");
//    QPixmap *plane_pic = new QPixmap(":/images/plane.png");

    QGraphicsScene *scene = new QGraphicsScene(this);

    int waypoint_y = 408;
    //These parameters will be used for arriving to the first landing place
    int place_1_x = 467;
    int place_1_y = 258;
    int waypoint_1_x = 467;
    int plane_1_ang = 0;
    //These parameters will be used for arriving to the second landing place
    int place_2_x = 657;
    int place_2_y = 291;
    int waypoint_2_x = 657;
    int plane_2_ang = 0;
    //These parameters will be used for arriving to the third landing place
    int place_3_x = 899;
    int place_3_y = 292;
    int waypoint_3_x = 899;
    int plane_3_ang = 0;

    //These parameters will be used for arriving to the fourth landing place
    int place_4_x = 1091;
    int place_4_y = 261;
    int waypoint_4_x = 1091;
    int plane_4_ang = 0;

    QTimer *clock1 = new QTimer(this);
    QTimer *clock2 = new QTimer(this);
    QTimer *clock3 = new QTimer(this);
    QTimer *clock4 = new QTimer(this);
    QTimer *clock5 = new QTimer(this);
    QTimer *clock6 = new QTimer(this);
    QTimer *clock7 = new QTimer(this);
    QTimer *clock8 = new QTimer(this);


    explicit Airport(QWidget *parent = nullptr);
    ~Airport();
signals:
    void notifyNewAgentAdded(Agent*);
    void notifyNewResourceAdded(Resource*);

    void trigger_arrive_2(QGraphicsItem*);
    void trigger_takeoff_2(QGraphicsItem*);
public slots:
    void addAgent(Agent*, int);
    void addResource(Resource*, int);

    //Arriving the first 2 places by frist runway
    void animate_arrive_place_1(QGraphicsItem*);
    void animate_arrive_place_2(QGraphicsItem*);
    //Arriving the 3,4 places by second runway
    void animate_arrive_place_3(QGraphicsItem*);
    void animate_arrive_place_4(QGraphicsItem*);

    void animate_takeoff_place_1(QGraphicsItem*);
    void animate_takeoff_place_2(QGraphicsItem*);
    void animate_takeoff_place_3(QGraphicsItem*);
    void animate_takeoff_place_4(QGraphicsItem*);

    void arrive_place_1(Agent*);
    void arrive_place_2(Agent*);
    void arrive_place_3(Agent*);
    void arrive_place_4(Agent*);
    void takeoff_place_1(Agent*);
    void takeoff_place_2(Agent*);
    void takeoff_place_3(Agent*);
    void takeoff_place_4(Agent*);

private:
    int get_place_x(int) const;
    int get_place_y(int) const;
};

#endif // AIRPORT_H
