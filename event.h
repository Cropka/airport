#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include "resource.h"
#include "agent.h"

class Event
{
public:
    explicit Event(int _timeOfOccuring, int _priority, std::vector<Agent>* _agents, std::vector<Resource>* _resources,
                   std::vector<Event>* _subevents);
    Event(const Event&);
    Event(Event&&);
    Event& operator=(Event&&);
    int timeOfOccuring;
    int priority;
    std::vector<Resource> *resources;
    std::vector<Agent> *agents; //event may initialise some agents, that need to be displayed on a GUI
    std::vector<Event> *subevents;
};

#endif // EVENT_H
