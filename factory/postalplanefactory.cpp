#include "postalplanefactory.h"

PostalPlaneFactory::PostalPlaneFactory(QObject *parent)
    : AgentFactory{parent}
{

}

PostalPlane *PostalPlaneFactory::createAgent(int priority)
{
    std::cerr<<"New postal plane created (priority: "<<priority<<")"<<std::endl;
    PostalPlane* newPlane = new PostalPlane(++counter);
    newPlane->priority=priority;
    return newPlane;
}

int PostalPlaneFactory::counter = 0;
