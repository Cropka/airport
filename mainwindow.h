#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include "simulator.h"
#include "presimulationmenu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Airport *airport;
    Simulator *simulator;
    Controller *controller;
    PreSimulationMenu *pre_sim_menu;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

};

#endif // MAINWINDOW_H
