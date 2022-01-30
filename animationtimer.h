#ifndef ANIMATIONTIMER_H
#define ANIMATIONTIMER_H

#include <QTimer>
#include <QObject>
#include "agent.h"

class AnimationTimer : public QTimer
{
    Q_OBJECT
    Agent *agent;
public:
    explicit AnimationTimer(QObject *parent = nullptr);
    void start(Agent*, int);
private slots:
    void onTimeout();
signals:
    void nextStep(Agent*);
};

#endif // ANIMATIONTIMER_H
