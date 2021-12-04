#ifndef AIRPORT_H
#define AIRPORT_H

#include <QObject>
#include <vector>
#include "agent.h"
#include "resource.h"

//this class is a link from the backend to the GUI. GUI may take all of the coordinates and object types from here.
//(fields positionX, positionY, type from classes agent and resource)
class airport : public QObject
{
    Q_OBJECT
public:
    explicit airport(QObject *parent = nullptr);
    std::vector<agent> agents; //vector of all agents
    std::vector<resource> resources; //vector of all resources
signals:

public slots:
//here need to appear some slots to add new agents/resources and to change their current positions.
};

#endif // AIRPORT_H
