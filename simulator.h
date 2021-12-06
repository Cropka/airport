#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include "postalplane.h"
#include "passangerplane.h"

/**
 * @brief The simulator class
 * Used to generate the events with all parameters, including time of occuring.
 */

//can be hardcoded at the beginning.
class Simulator : public QObject
{
    Q_OBJECT
public:
    explicit Simulator(QObject *parent = nullptr);
    virtual ~Simulator();

signals:
    void requestLanding(Agent* agent);

public slots:
    void simulation1();
};

#endif // SIMULATOR_H
