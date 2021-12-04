#ifndef AGENT_H
#define AGENT_H

#include <QObject>

//this class is for everything, which needs to be displayed, but cannot be classified as a resource. ex. planes.
class agent : public QObject
{
    Q_OBJECT
public:
    int id=-2;
    //coordinates are needed by the GUI. They need to be given at the constructor of each subclass. Default: 0, 0.
    float positionX=0.0;
    float positionY=0.0;
    explicit agent(QObject *parent = nullptr);
    std::string type="empty_agent";//different for each inheriting class. Given at constructor.

signals:

public slots:
};

#endif // AGENT_H
