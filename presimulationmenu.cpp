#include "presimulationmenu.h"

PreSimulationMenu::PreSimulationMenu(QWidget *parent)
    : QWidget{parent}
{
    menu_layout = new QGridLayout(this);
    spacer = new QSpacerItem(500, 500);
    start_sim_button = new QPushButton("Start simulation", this);
    add_passanger_plane_button = new QPushButton("Add passanger plane", this);
    add_postal_plane_button = new QPushButton("Add postal plane", this);
    add_runway_button = new QPushButton("Add runway", this);
    add_gateway_button = new QPushButton("Add gateway", this);
    add_ramp_stairs_button = new QPushButton("Add ramp stairs", this);
    add_bus_button = new QPushButton("Add new bus", this);

    menu_layout->addWidget(start_sim_button, 4, 3);
    menu_layout->addWidget(add_passanger_plane_button, 1, 2);
    menu_layout->addWidget(add_postal_plane_button, 1, 3);
    menu_layout->addWidget(add_ramp_stairs_button, 1, 4);
    menu_layout->addWidget(add_bus_button, 2, 2);
    menu_layout->addWidget(add_runway_button, 3, 2);
    menu_layout->addWidget(add_gateway_button, 3, 3);

    menu_layout->addItem(spacer, 1, 1, 4, 1);
    menu_layout->addItem(spacer, 1, 5, 4, 1);
    this->setLayout(menu_layout);
}

void PreSimulationMenu::connectButtons(Simulator* simulator)
{
    QObject::connect(add_passanger_plane_button, &QPushButton::clicked, simulator, &Simulator::addNewPassangerPlane);
    QObject::connect(add_postal_plane_button, &QPushButton::clicked, simulator, &Simulator::addNewPostalPlane);
    QObject::connect(add_bus_button, &QPushButton::clicked, simulator, &Simulator::addNewBus);
    QObject::connect(add_ramp_stairs_button, &QPushButton::clicked, simulator, &Simulator::addNewRampStairs);
    QObject::connect(add_gateway_button, &QPushButton::clicked, simulator, &Simulator::addNewGateway);
    QObject::connect(add_runway_button, &QPushButton::clicked, simulator, &Simulator::addNewRunway);
    QObject::connect(start_sim_button, &QPushButton::clicked, simulator, &Simulator::startSimulation);
}
