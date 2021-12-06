#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <agent.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

public slots:
    void landingRequested(Agent*);
};

#endif // CONTROLLER_H
