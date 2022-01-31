#include "landingspotfactory.h"

LandingSpotFactory::LandingSpotFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

LandingSpot *LandingSpotFactory::createResource()
{
    std::cerr<<"New LandingSpot created!"<<std::endl;
    return new LandingSpot(++counter);
}

int LandingSpotFactory::counter = 0;
