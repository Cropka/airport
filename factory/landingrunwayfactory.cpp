#include "landingrunwayfactory.h"

LandingRunwayFactory::LandingRunwayFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

LandingRunway *LandingRunwayFactory::createResource()
{
    std::cerr<<"New landing runway created!"<<std::endl;
    return new LandingRunway(++counter);
}

int LandingRunwayFactory::counter = 0;
