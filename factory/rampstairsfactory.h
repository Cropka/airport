#ifndef RAMPSTAIRSFACTORY_H
#define RAMPSTAIRSFACTORY_H

#include "agentfactory.h"
#include "rampstairs.h"

class RampStairsFactory : public AgentFactory
{
    static int counter;
public:
    explicit RampStairsFactory(QObject *parent = nullptr);
    virtual RampStairs* createAgent(int priority=5) override;
};

#endif // RAMPSTAIRSFACTORY_H
