#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    airport = new Airport(this);
    simulator = new Simulator(airport, this);
    controller = new Controller(airport, this);

    read_config_button = new QPushButton("Read config", this);
    read_config_button->setGeometry(1500, 200, 120, 40);
    get_filename_dialog = new QFileDialog(this);

    start_sim = new QPushButton("Start Simulation", this);
    start_sim->setGeometry(1500, 300, 120, 40);
    stop_sim = new QPushButton("Stop Simulation", this);
    stop_sim->setGeometry(1500, 400, 120, 40);
    setCentralWidget(airport);

    connect(start_sim, SIGNAL(clicked()), simulator, SLOT(startSimulation()));
    connect(stop_sim, SIGNAL(clicked()), simulator, SLOT(stopSimulation()));
    connect(read_config_button, SIGNAL(clicked()), this, SLOT(read_config()));
    connect(simulator, SIGNAL(requestLanding(Agent*)), controller, SLOT(landingRequested(Agent*)));
    connect(simulator, SIGNAL(requestTakeoff(Agent*)), controller, SLOT(takeoffRequested(Agent*)));
    connect(airport, SIGNAL(requestDocking(Agent*,int)), controller, SLOT(dockingRequested(Agent*,int)));
    connect(airport, SIGNAL(takeoffFinished(Agent*)), controller, SLOT(takeoffFinished(Agent*)));
    connect(airport, SIGNAL(docked(Agent*,int)), controller, SLOT(dockingFinished(Agent*,int)));
    connect(simulator, SIGNAL(newFreedResource_sim()), controller, SLOT(newFreeResource()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::read_config()
{
    QString filename = get_filename_dialog->getOpenFileName(this, QString("Provide config filename"));
    simulator->readConfigFile(filename.toStdString());
}

