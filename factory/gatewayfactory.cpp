#include "gatewayfactory.h"

GatewayFactory::GatewayFactory(QObject *parent)
    : ResourceFactory{parent}
{

}

Gateway *GatewayFactory::createResource()
{
    return new Gateway(++counter);
}

int GatewayFactory::counter = 0;
