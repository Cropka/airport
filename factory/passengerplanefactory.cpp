#include "passengerplanefactory.h"

PassengerPlaneFactory::PassengerPlaneFactory(QObject *parent)
    : AgentFactory{parent}
{

}

PassangerPlane *PassengerPlaneFactory::createAgent(int priority)
{
    std::cerr<<"New passanger plane created (priority: "<<priority<<")"<<std::endl;
    PassangerPlane* newPlane = new PassangerPlane(++counter);
    newPlane->priority=priority;
    return newPlane;
}

int PassengerPlaneFactory::counter = 0;
