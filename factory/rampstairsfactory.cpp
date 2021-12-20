#include "rampstairsfactory.h"

RampStairsFactory::RampStairsFactory(QObject *parent)
    : AgentFactory{parent}
{

}

RampStairs *RampStairsFactory::createAgent()
{
    std::cerr<<"New rampstairs created!"<<std::endl;
    return new RampStairs(++counter);
}

int RampStairsFactory::counter = 0;
