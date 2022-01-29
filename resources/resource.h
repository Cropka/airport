#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QPointF>
#include <string>

class Resource : public QObject
{
protected:
    Q_OBJECT
public:
    int id;
    bool busy;
    QPointF position;
    void markTaken(){ busy=true; }
    void markFree(){
        busy=false;
        emit(freed());
    }
    explicit Resource(int _id, QObject *parent = nullptr);
    Resource(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    explicit Resource(int _id, QPointF pos, QObject *parent = nullptr);
    bool isBusy() { return busy; }
    virtual std::string type() = 0;

signals:
    void freed();
//signal signaling outcome of isBusy method
public slots:
//slot asking about business
};

#endif // RESOURCE_H
