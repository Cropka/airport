#include "controller.h"
#include <iostream>
#include <algorithm>
#include <cassert>


Controller::Controller(Airport * _airport, QObject *parent)
    : QObject(parent)
{
    airport = _airport;
    event_handler = new QTimer(this);
    connect(event_handler, SIGNAL(timeout()), this, SLOT(runFirstDoableEvent()));
    event_handler->start(200);
}

Controller::~Controller()
{
    while (!event_queue.empty()) event_queue.pop_back();
}

int Controller::AreResourcesFree(ResourceBundle& resources, std::vector<Resource*> &resources_found)
{

    for (auto&& resource : resources) {
        bool found = false;
        for (auto airport_resource : airport->resources) {
            if (resource.first == airport_resource->type() && !airport_resource->isBusy()) {
                if (resource.second.empty()) {
                    found = true;
                    resources_found.push_back(airport_resource);
                    break;
                } else {
                    if(std::find(resource.second.begin(), resource.second.end(), airport_resource->id) != resource.second.end()) {
                        found = true;
                        resources_found.push_back(airport_resource);
                        break;
                    }
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void Controller::acknowledgeNewAgent(Agent *)
{

}

void Controller::acknowledgeNewResource(Resource *)
{

}

void Controller::landingRequested(Agent* agent)
{
    ResourceBundle resources = ResourceBundle();
    std::pair<std::string, std::vector<int>> resource;
    resource.first = "landing runway";
    resource.second = std::vector<int>();
    resources.push_back(resource);
    Event *event = new Event(agent, resources, "landing");
    event_queue.push_back(event);
    requeue();//resetting the queue
//    runFirstDoableEvent();
}

void Controller::takeoffRequested(Agent* agent)
{
    int spot = airport->determine_spot(agent);
    if (!spot) return;
    ResourceBundle resources = ResourceBundle();
    std::pair<std::string, std::vector<int>> resource;
    resource.first = "takeoff runway";
    std::vector<int> resource_ids;
    resource_ids.push_back(1);
    resource.second = resource_ids;
    resources.push_back(resource);
    if (spot > 2) {
        std::pair<std::string, std::vector<int>> resource2;
        resource2.first = "takeoff runway";
        std::vector<int> resource2_ids;
        resource2_ids.push_back(2);
        resource2.second = resource2_ids;
        resources.push_back(resource2);
    }
    Event *event = new Event(agent, resources, "takeoff");
    event_queue.push_back(event);
    requeue();//resetting the queue
//    runFirstDoableEvent();
}

void Controller::takeoffFinished(Agent *agent)
{
    //    for (auto res : airport->resources) {
    //        if (res->type() == "takeoff runway" && res->id == 1) {
    //            res->markFree();
    //        }
    //    }
    agent->state = "in air";
}

void Controller::dockingFinished(Agent *agent, int place)
{
    for (auto res : airport->resources) {
        if (res->type() == "takeoff runway") {
            if (place < 3 && res->id == 1) {
                res->markFree();
            } else if (place > 2 && res->id == 2) {
                res->markFree();
            }
        }
    }
    agent->state = "landed";
}

void Controller::dockingRequested(Agent *agent, int runway)
{
    ResourceBundle resources = ResourceBundle();
    std::pair<std::string, std::vector<int>> resource;
    resource.first = "takeoff runway";
    std::vector<int> resource_ids;
    resource_ids.push_back(runway);
    resource.second = resource_ids;
    resources.push_back(resource);

    std::pair<std::string, std::vector<int>> resource2;
    resource2.first = "landing spot";
    std::vector<int> resource2_ids;
    if (runway == 2)
        runway++;
    resource2_ids.push_back(runway);
    resource2_ids.push_back(runway + 1);
    resource2.second = resource2_ids;
    resources.push_back(resource2);

    Event *event = new Event(agent, resources, "docking");
    event_queue.push_back(event);
    requeue();//resetting the queue
//    runFirstDoableEvent();
}

void Controller::newFreeResource(){
//    runFirstDoableEvent();
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
    std::vector<Event*> newQueue;
    int currentPriority=0;//highest priority goes first
    while(!event_queue.empty()){
        for (Event* event : event_queue){
            if(event->priority==currentPriority){
                newQueue.push_back(event);
                event_queue.erase(std::remove(event_queue.begin(), event_queue.end(), event), event_queue.end());
            }
        }
        currentPriority++;
    }
    event_queue=newQueue;
    for (Event* event : event_queue){//highering the priority of every plane that is still waiting by one.
        if(event->priority>0){//but it couldn't go below 0.
            event->priority--;
        }
    }
}

void Controller::runEvent(Event *event, std::vector<Resource *> resources)
{
    if (event->type == "landing") {
        airport->arrive_landing_runway(event->agent, resources[0]->id);
        event->agent->state = "docking";
    }

    if (event->type == "takeoff") {
        int spot = airport->determine_spot(event->agent);
        airport->takeoff(event->agent, spot);
        event->agent->state = "taking off";
    }

    if (event->type == "docking") {
        for (auto res : resources) {
            if (res->type() == "landing spot") {
                airport->dock(event->agent, res->id);
            }
            if (res->type() == "takeoff runway") {
                for (auto res2 : airport->resources) {
                    if (res2->type() == "landing runway" && res2->id == res->id) {
                        res2->markFree();
                    }
                }
            }
        }
    }

    for (auto res : resources) {
        res->markTaken();
    }
}

//that function finds first event from the queue, which can be performed with the available resources.
//it's returning int, because it cannot just return agent*, as it may result in non finding one which is possible to perform.
bool Controller::runFirstDoableEvent(){
    event_queue_mutex.lock();
//    std::cerr << "event queue sizze: " << event_queue.size() << std::endl;
//    if (event_queue.size() > 0) {
//        std::cerr << "event 1 type = " << event_queue[0]->type << std::endl;
//    }
//    if (event_queue.size() == 2) {
//        std::cerr << "event 2 type = " << event_queue[0]->type << std::endl;
//    }
    airport->debugResources();
    for (Event* event : event_queue){
        std::vector<Resource*> resources_needed;
        if (AreResourcesFree(event->resources, resources_needed)){
              event_queue.erase(std::remove(event_queue.begin(), event_queue.end(), event), event_queue.end());
              runEvent(event, resources_needed);
              event_queue_mutex.unlock();
              return true;
        }
    }
    event_queue_mutex.unlock();
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
