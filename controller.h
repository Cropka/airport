#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <queue>
#include <utility>//this is for std::pair
#include "agent.h"
#include "airport.h"
#include "event.h"


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
    std::vector<std::pair<Agent*, std::string>> agent_queue;//agent and name of resource that it needs. Basically an operation.
    void requeue();
public:
    explicit Controller(Airport *_airport, QObject *parent = nullptr);
    virtual ~Controller();
    int isResourceFree(std::string);
    int runDoableEvents();//run all events that can be run
    bool runFirstDoableEvent();//if no doable event with current resources, returns false. Otherwise -> true.
public slots:
    void acknowledgeNewAgent(Agent*);
    void acknowledgeNewResource(Resource*);
    void landingRequested(Agent*);
    void takeoffRequested(Agent*);
    void newFreeResource();//this is activated, when any resource is freed. Then, controller could try to run some of the queued tasks(agents)
};

#endif // CONTROLLER_H
