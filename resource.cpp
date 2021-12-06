#include "resource.h"


Resource::Resource(int _id, QObject *parent)
    : QObject(parent), id(_id), busy(false)
{
   position = QPointF(0.0, 0.0);
}

Resource::Resource(int _id, float pos_x, float pos_y, QObject *parent)
    : QObject(parent), id(_id), busy(false), position(pos_x, pos_y)
{

}

Resource::Resource(int _id, QPointF pos, QObject *parent)
    : QObject(parent), id(_id), busy(false), position(pos)
{

}
