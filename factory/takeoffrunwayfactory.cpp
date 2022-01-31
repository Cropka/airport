#include "takeoffrunwayfactory.h"

TakeoffRunwayFactory::TakeoffRunwayFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

TakeoffRunway *TakeoffRunwayFactory::createResource()
{
    std::cerr<<"New takeoff runway created!"<<std::endl;
    return new TakeoffRunway(++counter);
}

int TakeoffRunwayFactory::counter = 0;
