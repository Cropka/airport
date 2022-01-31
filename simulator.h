#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QTimer>
#include "postalplane.h"
#include "passangerplane.h"
#include "airport.h"
#include "passengerplanefactory.h"
#include "postalplanefactory.h"
#include "busfactory.h"
#include "rampstairsfactory.h"
#include "gatewayfactory.h"
#include "landingrunwayfactory.h"
#include "landingspotfactory.h"
#include "takeoffrunwayfactory.h"
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
    LandingRunwayFactory landing_runway_factory;
    LandingSpotFactory landing_spot_factory;
    TakeoffRunwayFactory takeoff_runway_factory;
    QTimer* event_generator;
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
    void stopSimulation();
    void addNewPassangerPlane(int place, int priority);
    void addNewPostalPlane(int place, int priority);
    void addNewBus(int place);
    void addNewRampStairs(int place);
    void addNewGateway(int place);
    void addNewLandingRunway(int place);
    void addNewTakeoffRunway(int place);
    void addNewLandingSpot(int place);
    void newFreedResource();
private slots:
    void generateEvent();
};

#endif // SIMULATOR_H
