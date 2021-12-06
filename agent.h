#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QPointF>

//this class is for everything, which needs to be displayed, but cannot be classified as a resource. ex. planes.
class Agent : public QObject
{
protected:
    Q_OBJECT
public:
    int id;
    QPointF position; //coordinates are needed by the GUI. They need to be given at the constructor of each subclass. Default: 0, 0.

    explicit Agent(int _id, QObject *parent = nullptr);
    Agent(int _id, float pos_x, float pos_y, QObject *parent);
    virtual std::string type() = 0;
signals:

public slots:
};

#endif // AGENT_H
