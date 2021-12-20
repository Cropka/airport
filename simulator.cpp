#include "simulator.h"

Simulator::Simulator(Airport *_airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
    config=new ConfigParser(airport);
    connectParser();
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

void Simulator::connectParser(){
    QObject::connect(config, &ConfigParser::createPassangerPlane, this, &Simulator::addNewPassangerPlane);
    QObject::connect(config, &ConfigParser::createPostalPlane, this, &Simulator::addNewPostalPlane);
    QObject::connect(config, &ConfigParser::createBus, this, &Simulator::addNewBus);
    QObject::connect(config, &ConfigParser::createRampstairs, this, &Simulator::addNewRampStairs);
    QObject::connect(config, &ConfigParser::createGateway, this, &Simulator::addNewGateway);
    QObject::connect(config, &ConfigParser::createRunway, this, &Simulator::addNewRunway);
}

void Simulator::readConfigFile(){
    config->readObjects(filename);//should be changed! It should be taken from the user input!
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
