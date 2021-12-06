#ifndef AIRPORT_H
#define AIRPORT_H

#include <QObject>
#include <vector>
#include "agent.h"
#include "resource.h"

//this class is a link from the backend to the GUI. GUI may take all of the coordinates and object types from here.
//(fields positionX, positionY, type from classes agent and resource)
class Airport : public QObject
{
    Q_OBJECT
public:
    std::vector<Agent> agents; //vector of all agents
    std::vector<Resource> resources; //vector of all resources

    explicit Airport(QObject *parent = nullptr);
signals:

public slots:
//here need to appear some slots to add new agents/resources and to change their current positions.
};

#endif // AIRPORT_H
