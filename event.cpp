#include "event.h"

Event::Event(Agent *_agent, ResourceBundle _resources, std::string _type)
{
    resources = _resources;
    agent = _agent;
    priority = agent->priority;
    type = _type;
}
