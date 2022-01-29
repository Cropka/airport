#include "controller.h"
#include <iostream>


Controller::Controller(Airport * _airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
}

Controller::~Controller()
{
    while (!agent_queue.empty()) agent_queue.pop_back();
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
    //Event *event = new Event(0, 0, nullptr, nullptr, nullptr);
    agent_queue.push_back(agent);
    requeue();//setting the queue
    std::cerr << "Received event: Plane landing; plane type: " << agent->agent_type() << "; plane id: " << agent->id << std::endl;
    agent->setPos(467, 1000);
    airport->arrive_place_2(agent);
}

void Controller::newFreeResource(){
    //check if we can run something and run it if so
}

/*
bool CompareEvents::operator()(Event e1, Event e2)
{
    if (e1.timeOfOccuring < e2.timeOfOccuring)
        return true;
    return false;
}
*/

//this function just goes through the queue and set it acknowledging the priority of the agents.
void Controller::requeue(){
    std::vector<Agent*> newQueue;
    int currentPriority=0;//highest priority goes first
    while(!agent_queue.empty()){
        for (Agent* a : agent_queue){
            if(a->priority==currentPriority){
                newQueue.push_back(a);
                agent_queue.erase(std::remove(agent_queue.begin(), agent_queue.end(), a), agent_queue.end());
            }
        }
        currentPriority++;
    }
    agent_queue=newQueue;
    for (Agent* a : agent_queue){//highering the priority of every plane that is still waiting by one.
        if(a!=0){//but it couldn't go below 0.
            a->priority--;
        }
    }
}

