#include "plane.h"
#include <iostream>

Plane::Plane(int _id, QObject *parent)
    : Agent(_id, parent)
{
    image = QPixmap(":/images/plane.png");
    setScale(0.025);
    setRotation(0);
    state = "in air";
}

Plane::Plane(int _id,  float pos_x, float pos_y, QObject *parent)
    : Agent(_id, pos_x, pos_y, parent)
{
    image = QPixmap(":/images/plane.png");
    setRotation(0);
    setScale(0.025);
    state = "in air";
}
