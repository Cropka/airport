#include "busfactory.h"

BusFactory::BusFactory(QObject *parent)
    : AgentFactory{parent}
{

}

Bus *BusFactory::createAgent(int priority)
{
    std::cerr<<"New bus created!"<<std::endl;
    return new Bus(++counter);
}

int BusFactory::counter = 0;
