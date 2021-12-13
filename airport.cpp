#include "airport.h"

Airport::Airport(QObject *parent) : QObject(parent)
{

}

void Airport::addAgent(Agent *agent)
{
    agents.push_back(agent);
    emit notifyNewAgentAdded(agent);
}

void Airport::addResource(Resource *resource)
{
    resources.push_back(resource);
    emit notifyNewResourceAdded(resource);
}
