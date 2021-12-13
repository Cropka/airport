#include "event.h"

Event::Event(int _timeOfOccuring, int _priority, std::vector<Agent> *_agents, std::vector<Resource>* _resources,
             std::vector<Event>* _subevents)
    : timeOfOccuring(_timeOfOccuring),
      priority(_priority)
{
    resources = _resources;
    subevents = _subevents;
    agents = _agents;
}

Event::Event(const Event &e)
{
    timeOfOccuring = e.timeOfOccuring;
    priority = e.priority;
    resources = e.resources;
    agents = e.agents;
    subevents = e.subevents;
}

Event::Event(Event &&e)
{
    timeOfOccuring = e.timeOfOccuring;
    priority = e.priority;
    resources = e.resources;
    agents = e.agents;
    subevents = e.subevents;

    e.resources = nullptr;
    e.agents = nullptr;
    e.subevents = nullptr;
}

Event &Event::operator=(Event &&e)
{
    timeOfOccuring = e.timeOfOccuring;
    priority = e.priority;
    resources = e.resources;
    agents = e.agents;
    subevents = e.subevents;

    e.resources = nullptr;
    e.agents = nullptr;
    e.subevents = nullptr;
    return *this;
}
