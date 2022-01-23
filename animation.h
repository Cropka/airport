#ifndef ANIMATION_H
#define ANIMATION_H

#include <QMainWindow>
//#include <mainwindow.h>

class Animation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr);
    ~Animation();

    //MainWindow *animate = new MainWindow(this);

    //QGraphicsItem *plane2;

    QPixmap *plane_pic1 = new QPixmap("/home/laxin/Pictures/plane.png");


};

#endif // ANIMATION_H
