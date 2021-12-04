#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <string>

class resource : public QObject
{
protected:
    Q_OBJECT
public:
    int id=-1;
    bool busy;
    //coordinates are needed by the GUI. They need to be given at the constructor of each subclass. Default: 0, 0.
    float positionX=0.0;
    float positionY=0.0;
public:
    explicit resource(QObject *parent = nullptr): QObject(parent), busy(false) {}
    std::string type="empty_resource";//different for each inheriting class. Given at constructor.
    bool isBusy(){
        return busy;
    }
signals:
//signal signaling outcome of isBusy method
public slots:
//slot asking about business
};

#endif // RESOURCE_H
