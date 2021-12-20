#include "runwayfactory.h"

RunwayFactory::RunwayFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

Runway *RunwayFactory::createResource()
{
    std::cerr<<"New runway created!"<<std::endl;
    return new Runway(++counter);
}

int RunwayFactory::counter = 0;
