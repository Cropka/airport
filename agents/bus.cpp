#include "bus.h"

Bus::Bus(int _id, QObject *parent)
    : Car(_id, parent)
{

}

Bus::Bus(int _id, float pos_x, float pos_y, QObject *parent)
    : Car(_id, pos_x, pos_y, parent)
{

}
