#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

//this class is for everything, which needs to be displayed, but cannot be classified as a resource. ex. planes.
class Agent : public QObject, public QGraphicsItem
{
protected:
    Q_OBJECT
public:
    int id;
    int priority=5;
    int rotation_tracker = 0;
    QPixmap image;
    explicit Agent(int _id, QObject *parent = nullptr);
    Agent(int _id, float pos_x, float pos_y, QObject *parent = nullptr);
    virtual std::string agent_type() = 0;
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
signals:

public slots:
};

#endif // AGENT_H
