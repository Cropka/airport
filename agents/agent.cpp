#include "agent.h"
#include <iostream>

Agent::Agent(int _id, QObject *parent)
    : QObject(parent), QGraphicsItem(nullptr), id(_id)
{
    setTransformOriginPoint(image.rect().center());
}

Agent::Agent(int _id, float pos_x, float pos_y, QObject *parent)
    : QObject(parent), QGraphicsItem(nullptr), id(_id)
{
    this->setPos(QPointF(pos_x, pos_y));
}

QRectF Agent::boundingRect() const
{
    return image.rect(); // + QMarginsF(0.5 * image.rect().width(), 0.5 * image.rect().height(), 0.5 * image.rect().width(), 0.5 * image.rect().height());
}

void Agent::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(boundingRect(), image, boundingRect());
}
