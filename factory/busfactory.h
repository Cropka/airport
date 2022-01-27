#ifndef BUSFACTORY_H
#define BUSFACTORY_H

#include "agentfactory.h"
#include "bus.h"

class BusFactory : public AgentFactory
{
    static int counter;
public:
    explicit BusFactory(QObject *parent = nullptr);
    virtual Bus* createAgent(int priority=5) override;
};

#endif // BUSFACTORY_H
