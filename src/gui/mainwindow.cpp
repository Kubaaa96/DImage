#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(ui->actionOpen_Image, &QAction::triggered, this, &MainWindow::printFromAction);
    //connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::printFromAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printFromAction()
{
}
