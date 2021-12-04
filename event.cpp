#include "event.h"

event::event(int _timeOfOccuring, std::vector<agent> *_agents, std::vector<resource>* _subeventsResources,
             std::vector<int> _subeventsLengths, std::vector<int> _subeventsDeadlines, std::vector<int> _subeventsPriorities,
             QObject *parent) : QObject(parent), timeOfOccuring(_timeOfOccuring), subeventsResources(*_subeventsResources),
             subeventsPriorities(_subeventsPriorities), subeventsLengths(_subeventsLengths), subeventsDeadlines(_subeventsDeadlines),
             agents(*_agents)
{
    //agents should be added to the class airport here. Probably with some signal-slot mechanism, alongside with time of occuring.
}
