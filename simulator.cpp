#include "simulator.h"

Simulator::Simulator(QObject *parent)
    : QObject(parent)
{

}

Simulator::~Simulator()
{

}

void Simulator::simulation1()
{
    PassangerPlane plane1(1);
    PostalPlane plane2(1);
    PostalPlane plane3(2);
    PostalPlane plane4(3);
    PassangerPlane plane5(2);
    emit requestLanding(&plane3);
    emit requestLanding(&plane1);
    emit requestLanding(&plane4);
    emit requestLanding(&plane2);
    emit requestLanding(&plane5);
}
