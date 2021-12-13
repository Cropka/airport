#include "simulator.h"

Simulator::Simulator(Airport *_airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
}

Simulator::~Simulator()
{

}

void Simulator::startSimulation()
{
    for (auto agent : airport->agents) {
        if (agent->type() == "postal plane" || agent->type() == "passanger plane") {
            emit requestLanding(agent);
        }
    }
}

void Simulator::addNewPassangerPlane()
{
    airport->addAgent(passanger_plane_factory.createAgent());
}

void Simulator::addNewPostalPlane()
{
    airport->addAgent(postal_plane_factory.createAgent());
}

void Simulator::addNewBus()
{
    airport->addAgent(bus_factory.createAgent());
}

void Simulator::addNewRampStairs()
{
    airport->addAgent(ramp_stairs_factory.createAgent());
}

void Simulator::addNewGateway()
{
    airport->addResource(gateway_factory.createResource());
}

void Simulator::addNewRunway()
{
    airport->addResource(runway_factory.createResource());
}
