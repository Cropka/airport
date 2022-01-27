#ifndef PASSENGERPLANEFACTORY_H
#define PASSENGERPLANEFACTORY_H

#include "agentfactory.h"
#include "passangerplane.h"

class PassengerPlaneFactory : public AgentFactory
{
    static int counter;
public:
    explicit PassengerPlaneFactory(QObject *parent = nullptr);
    virtual PassangerPlane* createAgent(int priority) override;

};

#endif // PASSENGERPLANEFACTORY_H
