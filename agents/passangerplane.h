#ifndef PASSANGERPLANE_H
#define PASSANGERPLANE_H

#include "plane.h"

class PassangerPlane : public Plane
{
public:
    explicit PassangerPlane(int _id, QObject *parent = nullptr);
    explicit PassangerPlane(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("passanger plane"); }
};

#endif // PASSANGERPLANE_H
