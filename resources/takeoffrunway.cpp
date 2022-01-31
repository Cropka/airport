#include "takeoffrunway.h"

TakeoffRunway::TakeoffRunway(int _id, QObject *parent)
    : Resource(_id, parent)
{

}

TakeoffRunway::TakeoffRunway(int _id, float pos_x, float pos_y, QObject *parent)
    : Resource(_id, pos_x, pos_y, parent)
{

}
