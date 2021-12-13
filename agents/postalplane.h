#ifndef POSTALPLANE_H
#define POSTALPLANE_H

#include "plane.h"

class PostalPlane : public Plane
{
public:
    explicit PostalPlane(int _id, QObject *parent = nullptr);
    explicit PostalPlane(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("postal plane"); }
};

#endif // POSTALPLANE_H
