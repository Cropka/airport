#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <queue>
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
    std::vector<Agent*> agent_queue;
    void requeue();
public:
    explicit Controller(Airport *_airport, QObject *parent = nullptr);
    virtual ~Controller();
    int isResourceFree(std::string);
public slots:
    void acknowledgeNewAgent(Agent*);
    void acknowledgeNewResource(Resource*);
    void landingRequested(Agent*);
};

#endif // CONTROLLER_H
