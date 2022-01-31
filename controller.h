#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <queue>
#include <utility>//this is for std::pair
#include "agent.h"
#include "airport.h"
#include "event.h"
#include <mutex>
#include <QTimer>


/*class CompareEvents
{
public:
    bool operator() (Event, Event);
};*/


class Controller : public QObject
{
    Q_OBJECT

    Airport *airport;
    //std::priority_queue<Event, std::vector<Event>, CompareEvents> event_queue;
    std::vector<Event*> event_queue;//agent and name of resource that it needs. Basically an operation.
    std::mutex event_queue_mutex;
    QTimer* event_handler;
    void requeue();
    void runEvent(Event*, std::vector<Resource*>);
public:
    explicit Controller(Airport *_airport, QObject *parent = nullptr);
    virtual ~Controller();
    int AreResourcesFree(ResourceBundle&, std::vector<Resource*> &resources_found);
    int runDoableEvents();//run all events that can be run   
public slots:
    void acknowledgeNewAgent(Agent*);
    void acknowledgeNewResource(Resource*);
    void landingRequested(Agent*);
    void takeoffRequested(Agent*);
    void takeoffFinished(Agent*);
    void dockingFinished(Agent*, int);
    void dockingRequested(Agent*, int);
    void newFreeResource();//this is activated, when any resource is freed. Then, controller could try to run some of the queued tasks(agents)
    bool runFirstDoableEvent();//if no doable event with current resources, returns false. Otherwise -> true.
};

#endif // CONTROLLER_H
