#ifndef GATEWAYFACTORY_H
#define GATEWAYFACTORY_H

#include "resourcefactory.h"
#include "gateway.h"

class GatewayFactory : public ResourceFactory
{
    static int counter;
public:
    explicit GatewayFactory(QObject *parent = nullptr);
    virtual Gateway* createResource() override;
};

#endif // GATEWAYFACTORY_H
