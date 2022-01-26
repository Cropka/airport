#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "airport.h"
#include "simulator.h"
#include "controller.h"
#include <QFileDialog>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    Airport* airport;
    Simulator* simulator;
    Controller* controller;

    QPushButton* read_config_button;
    QFileDialog* get_filename_dialog;
    QPushButton* start_sim;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void read_config();

};
#endif // MAINWINDOW_H
