#include "postalplanefactory.h"

PostalPlaneFactory::PostalPlaneFactory(QObject *parent)
    : AgentFactory{parent}
{

}

PostalPlane *PostalPlaneFactory::createAgent()
{
    std::cerr<<"New postal plane created!"<<std::endl;
    return new PostalPlane(++counter);
}

int PostalPlaneFactory::counter = 0;
