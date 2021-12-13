#include "passengerplanefactory.h"

PassengerPlaneFactory::PassengerPlaneFactory(QObject *parent)
    : AgentFactory{parent}
{

}

PassangerPlane *PassengerPlaneFactory::createAgent()
{
    return new PassangerPlane(++counter);
}

int PassengerPlaneFactory::counter = 0;
