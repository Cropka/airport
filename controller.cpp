#include "controller.h"
#include <iostream>


Controller::Controller(QObject *parent)
    : QObject(parent)
{

}

void Controller::landingRequested(Agent* agent)
{
    std::cout << "Received event: Plane landing; plane type: " << agent->type() << "; plane id: " << agent->id << std::endl;
}
