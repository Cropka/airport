#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include "postalplane.h"
#include "passangerplane.h"
#include "airport.h"
#include "passengerplanefactory.h"
#include "postalplanefactory.h"
#include "busfactory.h"
#include "rampstairsfactory.h"
#include "gatewayfactory.h"
#include "runwayfactory.h"
#include "configparser.h"

/**
 * @brief The simulator class
 * Used to generate the events with all parameters, including time of occuring.
 */

class Simulator : public QObject
{
    Q_OBJECT
    std::string filename="config_file";
    Airport *airport;
    ConfigParser *config;
    PassengerPlaneFactory passanger_plane_factory;
    PostalPlaneFactory postal_plane_factory;
    BusFactory bus_factory;
    RampStairsFactory ramp_stairs_factory;
    GatewayFactory gateway_factory;
    RunwayFactory runway_factory;
    void connectParser();//just some signals-slots connection definitions

public:
    explicit Simulator(Airport *_airport, QObject *parent = nullptr);
    virtual ~Simulator();

signals:
    void requestLanding(Agent*);
    void requestTakeoff(Agent*);
    void newFreedResource_sim();
public slots:
    void readConfigFile(std::string);
    void startSimulation();
    void startSimulation2();
    void addNewPassangerPlane(int place, int priority);
    void addNewPostalPlane(int place, int priority);
    void addNewBus(int place);
    void addNewRampStairs(int place);
    void addNewGateway(int place);
    void addNewRunway(int place);
    void newFreedResource();
};

#endif // SIMULATOR_H
