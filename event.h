#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <utility>
#include "resource.h"
#include "agent.h"

using ResourceBundle = std::vector<std::pair<std::string, std::vector<int>>>;

class Event
{
public:
    explicit Event(Agent* _agent, ResourceBundle _resources, std::string _type);
    int priority;
    ResourceBundle resources;
    std::string type;
    Agent *agent; //event may initialise some agents, that need to be displayed on a GUI
};

#endif // EVENT_H
