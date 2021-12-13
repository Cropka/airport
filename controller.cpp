#include "controller.h"
#include <iostream>


Controller::Controller(Airport * _airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
}

Controller::~Controller()
{
    while (!event_queue.empty()) event_queue.pop();
}

int Controller::isResourceFree(std::string r_type)
{
    for (auto resource : airport->resources) {
        if (resource->type() == r_type && !resource->isBusy()) {
            return resource->id;
        }
    }
    return 0;
}

void Controller::acknowledgeNewAgent(Agent *)
{

}

void Controller::acknowledgeNewResource(Resource *)
{

}

void Controller::landingRequested(Agent* agent)
{
    Event *event = new Event(0, 0, nullptr, nullptr, nullptr);
    event_queue.push(*event);
    std::cout << "Received event: Plane landing; plane type: " << agent->type() << "; plane id: " << agent->id << std::endl;
}

bool CompareEvents::operator()(Event e1, Event e2)
{
    if (e1.timeOfOccuring < e2.timeOfOccuring)
        return true;
    return false;
}
