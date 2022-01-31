#include "simulator.h"
#include <random>

Simulator::Simulator(Airport *_airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
    config=new ConfigParser(airport);
    connectParser();
    event_generator = new QTimer(this);
    QObject::connect(event_generator, &QTimer::timeout, this, &Simulator::generateEvent);
//    for(Resource* r : airport->resources){
//        connect(r, SIGNAL(freed), this, SLOT(newFreedResource));
//    }
}

Simulator::~Simulator()
{
    delete config;
}

void Simulator::startSimulation()
{
    event_generator->start(1000);
}

void Simulator::stopSimulation()
{
    event_generator->stop();
}

void Simulator::connectParser(){
    QObject::connect(config, &ConfigParser::createPassangerPlane, this, &Simulator::addNewPassangerPlane);
    QObject::connect(config, &ConfigParser::createPostalPlane, this, &Simulator::addNewPostalPlane);
    QObject::connect(config, &ConfigParser::createBus, this, &Simulator::addNewBus);
    QObject::connect(config, &ConfigParser::createRampstairs, this, &Simulator::addNewRampStairs);
    QObject::connect(config, &ConfigParser::createGateway, this, &Simulator::addNewGateway);
    QObject::connect(config, &ConfigParser::createLandingRunway, this, &Simulator::addNewLandingRunway);
    QObject::connect(config, &ConfigParser::createLandingSpot, this, &Simulator::addNewLandingSpot);
    QObject::connect(config, &ConfigParser::createTakeoffRunway, this, &Simulator::addNewTakeoffRunway);
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
    Resource* r = gateway_factory.createResource();
    connect(r, SIGNAL(freed), this, SLOT(newFreedResource));
    airport->addResource(r, place);
}

void Simulator::addNewLandingRunway(int place)
{
    Resource* r = landing_runway_factory.createResource();
    connect(r, SIGNAL(freed), this, SLOT(newFreedResource));
    airport->addResource(r, place);
}

void Simulator::addNewTakeoffRunway(int place)
{
    Resource* r = takeoff_runway_factory.createResource();
    connect(r, SIGNAL(freed), this, SLOT(newFreedResource));
    airport->addResource(r, place);
}

void Simulator::addNewLandingSpot(int place)
{
    Resource* r = landing_spot_factory.createResource();
    connect(r, SIGNAL(freed), this, SLOT(newFreedResource));
    airport->addResource(r, place);
}

void Simulator::newFreedResource(){
    emit newFreedResource_sim();
}

void Simulator::generateEvent()
{
    int size = airport->agents.size();
    int agent_choice = std::rand() % size;
    Agent* agent = airport->agents[agent_choice];
    if (agent->state == "in air") {
//        std::cerr << "agent ins state: " << agent->state << std::endl;
        agent->state = "scheduled";
        emit requestLanding(agent);
    } else if (agent->state == "landed") {
//        std::cerr << "agent ins state: " << agent->state << std::endl;
        agent->state = "scheduled";
        emit requestTakeoff(agent);
    } else {
//        std::cerr << "DUPPPA state: " << agent->state << std::endl;
    }
}
