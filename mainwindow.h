#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "controller.h"
#include "simulator.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Simulator *simulator;
    Controller *controller;
    QPushButton *start_sim1;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

};

#endif // MAINWINDOW_H
