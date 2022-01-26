#ifndef CAR_H
#define CAR_H

#include "agent.h"

class Car : public Agent
{
public:
    explicit Car(int _id, QObject *parent = nullptr);
    explicit Car(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string agent_type() override { return std::string("car"); }
};

#endif // CAR_H
