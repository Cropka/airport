#ifndef RAMPSTAIRS_H
#define RAMPSTAIRS_H

#include "car.h"

class RampStairs : public Car
{
public:
    explicit RampStairs(int _id, QObject *parent = nullptr);
    explicit RampStairs(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string agent_type() override { return std::string("ramp staris"); }
};

#endif // RAMPSTAIRS_H
