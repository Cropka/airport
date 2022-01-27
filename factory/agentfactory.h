#ifndef AGENTFACTORY_H
#define AGENTFACTORY_H

#include <QObject>
#include "agent.h"
#include <iostream>

class AgentFactory : public QObject
{
    Q_OBJECT
public:
    explicit AgentFactory(QObject *parent = nullptr);
    virtual Agent* createAgent(int priority) = 0;
signals:

};

#endif // AGENTFACTORY_H
