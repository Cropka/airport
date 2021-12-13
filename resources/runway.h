#ifndef RUNWAY_H
#define RUNWAY_H

#include "resource.h"

class Runway : public Resource
{
public:
    explicit Runway(int _id, QObject *parent = nullptr);
    Runway(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("runway"); }
};

#endif // RUNWAY_H
