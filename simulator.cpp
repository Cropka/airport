#include "simulator.h"

Simulator::Simulator(Airport *_airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
    config=new ConfigParser(airport);
    connectParser();
    for(Resource* r : airport->resources){
        connect(r, SIGNAL(freed), this, SLOT(newFreedResource));
    }
}

Simulator::~Simulator()
{

}

void Simulator::startSimulation()
{
    for (auto agent : airport->agents) {
        if (agent->agent_type() == "postal plane" || agent->agent_type() == "passanger plane") {
            emit requestLanding(agent);
        }
    }
}

void Simulator::startSimulation2()
{
    for (auto agent : airport->agents) {
        if (agent->agent_type() == "postal plane" || agent->agent_type() == "passanger plane") {
            emit requestTakeoff(agent);
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

void Simulator::readConfigFile(std::string filename){
    config->readObjects(filename);//should be changed! It should be taken from the user input!
}

void Simulator::addNewPassangerPlane(int place, int priority)
{
    airport->addAgent(passanger_plane_factory.createAgent(priority), place);
}

void Simulator::addNewPostalPlane(int place, int priority)
{
    airport->addAgent(postal_plane_factory.createAgent(priority), place);
}

void Simulator::addNewBus(int place)
{
    airport->addAgent(bus_factory.createAgent(), place);
}

void Simulator::addNewRampStairs(int place)
{
    airport->addAgent(ramp_stairs_factory.createAgent(), place);
}

void Simulator::addNewGateway(int place)
{
    airport->addResource(gateway_factory.createResource(), place);
}

void Simulator::addNewRunway(int place)
{
    airport->addResource(runway_factory.createResource(), place);
}

void Simulator::newFreedResource(){
    emit(newFreedResource_sim());
}
