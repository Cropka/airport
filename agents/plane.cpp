#include "plane.h"
#include <iostream>

Plane::Plane(int _id, QObject *parent)
    : Agent(_id, parent)
{
    std::cout<<"TEST"<<std::endl;

}

Plane::Plane(int _id, float pos_x, float pos_y, QObject *parent)
    : Agent(_id, pos_x, pos_y, parent)
{
    std::cout<<"TEST1"<<std::endl;

}
