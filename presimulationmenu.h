#ifndef PRESIMULATIONMENU_H
#define PRESIMULATIONMENU_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "simulator.h"

class PreSimulationMenu : public QWidget
{
    Q_OBJECT

    QGridLayout *menu_layout;
    QPushButton *start_sim_button;
    QPushButton *add_passanger_plane_button;
    QPushButton *add_postal_plane_button;
    QPushButton *add_runway_button;
    QPushButton *add_gateway_button;
    QPushButton *add_ramp_stairs_button;
    QPushButton *add_bus_button;
    QSpacerItem *spacer;

public:
    explicit PreSimulationMenu(QWidget *parent = nullptr);
    void connectButtons(Simulator *simulator);
signals:

public slots:
};

#endif // PRESIMULATIONMENU_H
