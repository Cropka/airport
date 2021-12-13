#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    airport = new Airport(this);
    simulator = new Simulator(airport, this);
    controller = new Controller(airport, this);
    pre_sim_menu = new PreSimulationMenu(this);
    pre_sim_menu->connectButtons(simulator);
    this->setCentralWidget(pre_sim_menu);
    QObject::connect(simulator, &Simulator::requestLanding, controller, &Controller::landingRequested);
}

MainWindow::~MainWindow()
{

}
