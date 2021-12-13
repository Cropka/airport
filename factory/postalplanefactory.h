#ifndef POSTALPLANEFACTORY_H
#define POSTALPLANEFACTORY_H

#include "agentfactory.h"
#include "postalplane.h"

class PostalPlaneFactory : public AgentFactory
{
    static int counter;
public:
    explicit PostalPlaneFactory(QObject *parent = nullptr);
    virtual PostalPlane *createAgent() override;
};

#endif // POSTALPLANEFACTORY_H
