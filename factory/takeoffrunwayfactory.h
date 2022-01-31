#ifndef TAKEOFFRUNWAYFACTORY_H
#define TAKEOFFRUNWAYFACTORY_H

#include "resourcefactory.h"
#include "takeoffrunway.h"

class TakeoffRunwayFactory : public ResourceFactory
{
    static int counter;
public:
    explicit TakeoffRunwayFactory(QObject *parent = nullptr);
    virtual TakeoffRunway* createResource() override;
};

#endif // TAKEOFFRUNWAYFACTORY_H
