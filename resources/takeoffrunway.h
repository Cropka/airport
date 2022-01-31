#ifndef TAKEOFFRUNWAY_H
#define TAKEOFFRUNWAY_H

#include "resource.h"

class TakeoffRunway : public Resource
{
public:
    explicit TakeoffRunway(int _id, QObject *parent = nullptr);
    TakeoffRunway(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("takeoff runway"); }
};

#endif // TAKEOFFRUNWAY_H
