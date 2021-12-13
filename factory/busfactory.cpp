#include "busfactory.h"

BusFactory::BusFactory(QObject *parent)
    : AgentFactory{parent}
{

}

Bus *BusFactory::createAgent()
{
    return new Bus(++counter);
}

int BusFactory::counter = 0;
