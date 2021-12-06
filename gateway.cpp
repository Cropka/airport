#include "gateway.h"

Gateway::Gateway(int _id, QObject *parent)
    : Resource(_id, parent)
{

}

Gateway::Gateway(int _id, float pos_x, float pos_y, QObject *parent)
    : Resource(_id, pos_x, pos_y, parent)
{

}
