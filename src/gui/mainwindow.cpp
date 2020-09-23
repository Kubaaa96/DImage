#include "mainwindow.h"
#include "imageviewer.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QImageReader>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageViewer = new ImageViewer();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(imageViewer);
    ui->centralwidget->setLayout(layout);
    connect(ui->actionOpen_Image, &QAction::triggered, this, &MainWindow::openFile);
    //connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::printFromAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "D:", tr("Image Files (*.png *.jpg *.bmp)"));
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            tr("Cannot load %1: %2")
                .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return;
    }
    imageViewer->setPhoto(newImage);
}
