#include "passengerplanefactory.h"

PassengerPlaneFactory::PassengerPlaneFactory(QObject *parent)
    : AgentFactory{parent}
{

}

PassangerPlane *PassengerPlaneFactory::createAgent()
{
    std::cerr<<"New passanger plane created!"<<std::endl;
    return new PassangerPlane(++counter);
}

int PassengerPlaneFactory::counter = 0;
