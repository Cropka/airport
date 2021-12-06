#include "agent.h"

Agent::Agent(int _id, QObject *parent)
    : QObject(parent),
      id(_id)
{

}

Agent::Agent(int _id, float pos_x, float pos_y, QObject *parent)
    : QObject(parent),
      id(_id),
      position(pos_x, pos_y)
{

}
