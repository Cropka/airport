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

//can be hardcoded at the beginning.

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

public slots:
    void readConfigFile();//the filename should be read from GUI. For now its hardcoded (but it should probably change).
    void startSimulation();
    void addNewPassangerPlane();
    void addNewPostalPlane();
    void addNewBus();
    void addNewRampStairs();
    void addNewGateway();
    void addNewRunway();
};

#endif // SIMULATOR_H
