#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <animation.h>
#include <QTimeLine>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    Ui::MainWindow *ui;

    QGraphicsItem *plane;
    QGraphicsItem *plane1;
    QGraphicsItem *plane2;
    QGraphicsItem *plane3;
    QGraphicsItem *airport;

    QPixmap *airport_pic = new QPixmap("/home/laxin/Pictures/correct_airport_pop.png");
    QPixmap *plane_pic = new QPixmap("/home/laxin/Pictures/plane.png");

    QGraphicsScene *scene = new QGraphicsScene(this);

    int waypoint_y = 408;
    //These parameters will be used for arriving to the first landing place
    int place_1_x = 467;
    int place_1_y = 258;
    int waypoint_1_x = 467;
    int plane_1_ang = 0;
    //These parameters will be used for arriving to the second landing place
    int place_2_x = 657;
    int place_2_y = 291;
    int waypoint_2_x = 657;
    int plane_2_ang = 0;
    //These parameters will be used for arriving to the third landing place
    int place_3_x = 899;
    int place_3_y = 292;
    int waypoint_3_x = 899;
    int plane_3_ang = 0;

    //These parameters will be used for arriving to the fourth landing place
    int place_4_x = 1091;
    int place_4_y = 261;
    int waypoint_4_x = 1091;
    int plane_4_ang = 0;


    QTimer *clock1 = new QTimer(this);
    QTimer *clock2 = new QTimer(this);
    QTimer *clock3 = new QTimer(this);
    QTimer *clock4 = new QTimer(this);
    QTimer *clock5 = new QTimer(this);
    QTimer *clock6 = new QTimer(this);
    QTimer *clock7 = new QTimer(this);
    QTimer *clock8 = new QTimer(this);


signals:
    void set_up(QGraphicsItem*);
    void set_up1(QGraphicsItem*);

public slots:
    void arrive_place_1(QGraphicsItem*);
    void arrive_place_2(QGraphicsItem*);
    void arrive_place_3(QGraphicsItem*);
    void arrive_place_4(QGraphicsItem*);

    void takeoff_place_1(QGraphicsItem*);
    void takeoff_place_2(QGraphicsItem*);
    void takeoff_place_3(QGraphicsItem*);
    void takeoff_place_4(QGraphicsItem*);

    void move_to_second();
    void move1();




};
#endif // MAINWINDOW_H
