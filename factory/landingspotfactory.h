#ifndef LANDINGSPOTFACTORY_H
#define LANDINGSPOTFACTORY_H

#include "resourcefactory.h"
#include "landingspot.h"

class LandingSpotFactory : public ResourceFactory
{
    static int counter;
public:
    explicit LandingSpotFactory(QObject *parent = nullptr);
    virtual LandingSpot* createResource() override;
};

#endif // LANDINGSPOTFACTORY_H
