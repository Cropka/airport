#include "landingspot.h"

LandingSpot::LandingSpot(int _id, QObject *parent)
    : Resource{_id, parent}
{

}

LandingSpot::LandingSpot(int _id, float pos_x, float pos_y, QObject *parent)
    : Resource(_id, pos_x, pos_y, parent)
{

}
