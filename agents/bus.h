#ifndef BUS_H
#define BUS_H

#include "car.h"

class Bus : public Car
{
public:
    explicit Bus(int _id, QObject *parent = nullptr);
    explicit Bus(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string agent_type() override { return std::string("bus"); }
};

#endif // BUS_H
