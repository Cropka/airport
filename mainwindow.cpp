#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    simulator = new Simulator(this);
    controller = new Controller(this);
    start_sim1 = new QPushButton("Start simulation #1", this);
    QObject::connect(simulator, &Simulator::requestLanding, controller, &Controller::landingRequested);
    QObject::connect(start_sim1, &QPushButton::clicked, simulator, &Simulator::simulation1);
}

MainWindow::~MainWindow()
{
    delete simulator;
    delete controller;
    delete start_sim1;
}
