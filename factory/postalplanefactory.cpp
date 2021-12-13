#include "postalplanefactory.h"

PostalPlaneFactory::PostalPlaneFactory(QObject *parent)
    : AgentFactory{parent}
{

}

PostalPlane *PostalPlaneFactory::createAgent()
{
    return new PostalPlane(++counter);
}

int PostalPlaneFactory::counter = 0;
