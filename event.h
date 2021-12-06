#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <vector>
#include "resource.h"
#include "agent.h"

class Event : public QObject
{
private:
    Q_OBJECT
public:
    explicit Event(int _timeOfOccuring, int _priority, std::vector<Agent>* _agents, std::vector<Resource>* _resources,
                   std::vector<Event>* _subevents, QObject *parent = nullptr);
    int timeOfOccuring;
    int priority;
    std::vector<Resource>& resources;
    std::vector<Agent>& agents; //event may initialise some agents, that need to be displayed on a GUI
    std::vector<Event>& subevents;
signals:

public slots:
};

#endif // EVENT_H
