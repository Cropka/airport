#ifndef GATEWAY_H
#define GATEWAY_H

#include "resource.h"

class Gateway : public Resource
{
public:

    explicit Gateway(int _id, QObject *parent = nullptr);
    Gateway(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string type() override { return std::string("gateway"); }
};

#endif // GATEWAY_H
