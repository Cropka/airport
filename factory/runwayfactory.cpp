#include "runwayfactory.h"

RunwayFactory::RunwayFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

Runway *RunwayFactory::createResource()
{
    return new Runway(++counter);
}

int RunwayFactory::counter = 0;
