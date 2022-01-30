#include "animationtimer.h"
#include <iostream>

AnimationTimer::AnimationTimer(QObject *parent)
    : QTimer{parent}
{
    connect(this, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void AnimationTimer::start(Agent *_agent, int interval)
{
    agent = _agent;
    QTimer::start(interval);
}

void AnimationTimer::onTimeout()
{
    emit nextStep(agent);
}
