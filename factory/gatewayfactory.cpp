#include "gatewayfactory.h"

GatewayFactory::GatewayFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

Gateway *GatewayFactory::createResource()
{
    std::cerr<<"New gateway created!"<<std::endl;
    return new Gateway(++counter);
}

int GatewayFactory::counter = 0;
