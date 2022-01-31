#ifndef LANDINGRUNWAYFACTORY_H
#define LANDINGRUNWAYFACTORY_H

#include "resourcefactory.h"
#include "landingrunway.h"

class LandingRunwayFactory : public ResourceFactory
{
    static int counter;
public:
    explicit LandingRunwayFactory(QObject *parent = nullptr);
    virtual LandingRunway* createResource() override;
};

#endif // LANDINGRUNWAYFACTORY_H
