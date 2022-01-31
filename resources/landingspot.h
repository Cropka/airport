#ifndef LANDINGSPOT_H
#define LANDINGSPOT_H

#include "resource.h"

class LandingSpot : public Resource
{
public:
    explicit LandingSpot(int _id, QObject *parent = nullptr);
    LandingSpot(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("landing spot"); }
};

#endif // LANDINGSPOT_H
