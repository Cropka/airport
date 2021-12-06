#ifndef PLANE_H
#define PLANE_H

#include "agent.h"

class Plane : public Agent
{
public:
    explicit Plane(int _id, QObject *parent = nullptr);
    explicit Plane(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("plane"); }
};

#endif // PLANE_H
