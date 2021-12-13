#include "rampstairsfactory.h"

RampStairsFactory::RampStairsFactory(QObject *parent)
    : AgentFactory{parent}
{

}

RampStairs *RampStairsFactory::createAgent()
{
    return new RampStairs(++counter);
}

int RampStairsFactory::counter = 0;
