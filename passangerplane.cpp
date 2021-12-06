#include "passangerplane.h"

PassangerPlane::PassangerPlane(int _id, QObject *parent)
    : Plane(_id, parent)
{

}

PassangerPlane::PassangerPlane(int _id, float pos_x, float pos_y, QObject *parent)
    : Plane(_id, pos_x, pos_y, parent)
{

}
