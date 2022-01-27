#include "rampstairsfactory.h"

RampStairsFactory::RampStairsFactory(QObject *parent)
    : AgentFactory{parent}
{

}

RampStairs *RampStairsFactory::createAgent(int priority)
{
    std::cerr<<"New rampstairs created!"<<std::endl;
    return new RampStairs(++counter);
}

int RampStairsFactory::counter = 0;
