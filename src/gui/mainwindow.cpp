#include "mainwindow.h"
#include "imagecontainer.h"
#include "imageviewer.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QImageReader>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageViewer = new ImageViewer();

    treeOptionWidget = new QTreeWidget();
    item = new QTreeWidgetItem();
    item->setCheckState(1, Qt::Unchecked);
    item->setText(1, "Test");
    treeOptionWidget->addTopLevelItem(item);
    treeOptionWidget->setMaximumWidth(250);

    creatingButtonToHideOptions();
    creatingContainerForImages();
    creatingButtonToHideContainer();
    settingUpMainLayout();
    connectingCommands();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete imageViewer;
    delete treeOptionWidget;
    delete testImage;
    delete containerWidgetImages;
    delete verticalImagesLayout;
    delete buttonImageViewHide;
    delete buttonOptionsHide;
}

void MainWindow::hideOptionWidget()
{
    if (treeOptionWidget->isHidden()) {
        treeOptionWidget->setHidden(false);
        buttonOptionsHide->setIcon(QIcon(":/mainWindow/ArrowLeft.png"));
    } else {
        treeOptionWidget->setHidden(true);
        buttonOptionsHide->setIcon(QIcon(":/mainWindow/arrowRight.png"));
    }
}

void MainWindow::hideImageLayout()
{
    if (containerWidgetImages->isHidden()) {
        buttonImageViewHide->setIcon(QIcon(":/mainWindow/arrowRight.png"));
        containerWidgetImages->setHidden(false);
    } else {
        buttonImageViewHide->setIcon(QIcon(":/mainWindow/ArrowLeft.png"));
        containerWidgetImages->setHidden(true);
    }
}

void MainWindow::creatingContainerForImages()
{
    containerWidgetImages = new ImageContainer();
    verticalImagesLayout = new QVBoxLayout();
    testImage = new QLabel();
    testImage->setText("Test Before Image");
    verticalImagesLayout->addWidget(testImage);
    containerWidgetImages->setLayout(verticalImagesLayout);
    containerWidgetImages->setMaximumWidth(250); // TODO Change Magic Numbers
}

void MainWindow::creatingButtonToHideContainer()
{
    buttonImageViewHide = new QPushButton();
    buttonImageViewHide->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    buttonImageViewHide->setMaximumWidth(30); // TODO Change Magic Numbers
    buttonImageViewHide->setIcon(QIcon(":/mainWindow/arrowRight.png"));
}

void MainWindow::creatingButtonToHideOptions()
{
    buttonOptionsHide = new QPushButton();
    buttonOptionsHide->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    buttonOptionsHide->setMaximumWidth(30); // TODO Change Magic Numbers
    //printf(icon.isNull() ? "true" : "false");
    buttonOptionsHide->setIcon(QIcon(":/mainWindow/ArrowLeft.png"));
}

void MainWindow::settingUpMainLayout()
{
    auto layout = new QHBoxLayout;
    layout->addWidget(containerWidgetImages);
    layout->addWidget(buttonImageViewHide);
    layout->addWidget(imageViewer);
    layout->addWidget(buttonOptionsHide);
    layout->addWidget(treeOptionWidget);
    layout->setStretch(0, 2);
    layout->setStretch(1, 1);
    layout->setStretch(2, 5);
    layout->setStretch(3, 1);
    layout->setStretch(4, 2);

    ui->centralwidget->setLayout(layout);
}

void MainWindow::connectingCommands()
{
    connect(ui->actionOpen_Image, &QAction::triggered, this, &MainWindow::openFile);
    connect(buttonOptionsHide, &QPushButton::pressed, this, &MainWindow::hideOptionWidget);
    connect(buttonImageViewHide, &QPushButton::pressed, this, &MainWindow::hideImageLayout);
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
