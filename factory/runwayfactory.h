#ifndef RUNWAYFACTORY_H
#define RUNWAYFACTORY_H

#include "resourcefactory.h"
#include "runway.h"

class RunwayFactory : public ResourceFactory
{
    static int counter;
public:
    explicit RunwayFactory(QObject *parent = nullptr);
    virtual Runway* createResource() override;
};

#endif // RUNWAYFACTORY_H
