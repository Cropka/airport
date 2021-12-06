#include "event.h"

Event::Event(int _timeOfOccuring, int _priority, std::vector<Agent> *_agents, std::vector<Resource>* _resources,
             std::vector<Event>* _subevents, QObject *parent)
    : QObject(parent),
      timeOfOccuring(_timeOfOccuring),
      priority(_priority),
      resources(*_resources),
      agents(*_agents),
      subevents(*_subevents)
{
    //agents should be added to the class airport here. Probably with some signal-slot mechanism, alongside with time of occuring.
}
