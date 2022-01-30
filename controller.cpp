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
    std::pair<Agent*, std::string> operation;
    operation.first=agent;
    operation.second="runway";
    agent_queue.push_back(operation);
    requeue();//resetting the queue
    std::cerr << "Received event: Plane landing; plane type: " << agent->agent_type() << "; plane id: " << agent->id << std::endl;

    airport->arrive_place_4(agent);
}

void Controller::takeoffRequested(Agent* agent)
{
    std::pair<Agent*, std::string> operation;
    operation.first=agent;
    operation.second="runway";
    agent_queue.push_back(operation);
    requeue();

    airport->takeoff_place_4(agent);
}

void Controller::newFreeResource(){
    runFirstDoableEvent();
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
    std::vector<std::pair<Agent*, std::string>> newQueue;
    int currentPriority=0;//highest priority goes first
    while(!agent_queue.empty()){
        for (std::pair<Agent*, std::string> op : agent_queue){
            if(op.first->priority==currentPriority){
                newQueue.push_back(op);
                agent_queue.erase(std::remove(agent_queue.begin(), agent_queue.end(), op), agent_queue.end());
            }
        }
        currentPriority++;
    }
    agent_queue=newQueue;
    for (std::pair<Agent*, std::string> op : agent_queue){//highering the priority of every plane that is still waiting by one.
        if(op.first->priority>0){//but it couldn't go below 0.
            op.first->priority--;
        }
    }
}

//that function finds first event from the queue, which can be performed with the available resources.
//it's returning int, because it cannot just return agent*, as it may result in non finding one which is possible to perform.
bool Controller::runFirstDoableEvent(){
    for (std::pair<Agent*, std::string> op : agent_queue){
        if (isResourceFree(op.second)){
              agent_queue.erase(std::remove(agent_queue.begin(), agent_queue.end(), op), agent_queue.end());
              //op.first.run_event;
              return true;
        }
    }
    return false;
}

int Controller::runDoableEvents(){
    bool flag=true;
    int counter=0;
    while(flag==true){
        flag=runFirstDoableEvent();
    }
    return counter;
}
