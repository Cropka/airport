#ifndef LANDINGRUNWAY_H
#define LANDINGRUNWAY_H

#include "resource.h"

class LandingRunway : public Resource
{
public:
    explicit LandingRunway(int _id, QObject *parent = nullptr);
    LandingRunway(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("landing runway"); }
};

#endif // LANDINGRUNWAY_H
