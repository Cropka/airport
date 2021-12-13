#include "plane.h"


Plane::Plane(int _id, QObject *parent)
    : Agent(_id, parent)
{

}

Plane::Plane(int _id, float pos_x, float pos_y, QObject *parent)
    : Agent(_id, pos_x, pos_y, parent)
{

}
