#include "car.h"

Car::Car(int _id, QObject *parent)
    : Agent(_id, parent)
{

}

Car::Car(int _id, float pos_x, float pos_y, QObject *parent)
    : Agent(_id, pos_x, pos_y, parent)
{
    this->setPos(QPointF(pos_x, pos_y));
}
