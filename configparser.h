#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <airport.h>
#include <QObject>

#define LINE_SIZE 500

/**
 * @brief The ConfigParser class
 * Object of this this class is created to read the config file and trigger agents and resources
 * instances to be created (via factory classes).
 * Config file has the form:
 * command position_x position_y
 * command position_x position_y
 * .
 * .
 * .
 * Commands are declared in the std::vector keywords.
 * It is preprocessed by C preprocessor, so it supports C-style comments, constant defines, macros...
 * Usage: just create object of the class with name of config file as an argument, then run readObjects() method.
 */

class ConfigParser : public QObject
{
    Q_OBJECT
public:
    Airport *airport;
    std::vector<std::string> keywords={"postalplane", "passengerplane", "rampstairs", "bus", "gateway", "runway"}; //definitions of commands in the config file
    ConfigParser(Airport *_airport, QObject *parent = nullptr);
    bool readObjects(std::string _filename);
    bool preprocess(std::istringstream& _iStream, std::string _filename);
    void emitSignal(std::string _indicator);
signals:
    void createPostalPlane();
    void createPassangerPlane();
    void createRampstairs();
    void createBus();
    void createGateway();
    void createRunway();
};

#endif // CONFIGPARSER_H
