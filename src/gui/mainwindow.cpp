#include "mainwindow.h"
#include "aboutwidget.h"
#include "imagecontainer.h"
#include "optionwidget.h"

#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageViewer = new ImageViewer();

    creatingButtonToHideOptions();
    creatingButtonToHideContainer();
    creatingContainerForImages();
    creatingOptionsWidget();
    settingUpMainLayout();
    connectingCommands();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete imageViewer;
    delete optionWidget;
    delete containerWidgetImages;
    delete buttonImageViewHide;
    delete buttonOptionsHide;
}

void MainWindow::creatingButtonToHideOptions()
{
    buttonOptionsHide = new QPushButton();
    buttonOptionsHide->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    buttonOptionsHide->setMaximumWidth(maximumWidthOfHidingButtons); // TODO Change Magic Numbers
    //printf(icon.isNull() ? "true" : "false");
    buttonOptionsHide->setIcon(QIcon(":/mainWindow/ArrowLeft.png"));
}

void MainWindow::creatingButtonToHideContainer()
{
    buttonImageViewHide = new QPushButton();
    buttonImageViewHide->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    buttonImageViewHide->setMaximumWidth(maximumWidthOfHidingButtons); // TODO Change Magic Numbers
    buttonImageViewHide->setIcon(QIcon(":/mainWindow/arrowRight.png"));
}

void MainWindow::creatingContainerForImages()
{
    containerWidgetImages = new ImageContainer(imageViewer, nullptr);
    containerWidgetImages->setMaximumWidth(maximumWidthOfSidesWidgets); // TODO Change Magic Numbers
}

void MainWindow::settingUpMainLayout()
{
    auto layout = new QHBoxLayout;
    layout->addWidget(containerWidgetImages);
    layout->addWidget(buttonImageViewHide);
    layout->addWidget(imageViewer);
    layout->addWidget(buttonOptionsHide);
    layout->addWidget(optionWidget);
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
    connect(ui->actionSave_asImage, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(buttonOptionsHide, &QPushButton::pressed, this, &MainWindow::hideOptionWidget);
    connect(buttonImageViewHide, &QPushButton::pressed, this, &MainWindow::hideImageLayout);
}

void MainWindow::creatingOptionsWidget()
{
    optionWidget = new OptionWidget();
    optionWidget->setMaximumWidth(maximumWidthOfSidesWidgets);
}

void MainWindow::hideOptionWidget()
{
    if (optionWidget->isHidden()) {
        optionWidget->setHidden(false);
        buttonOptionsHide->setIcon(QIcon(":/mainWindow/ArrowLeft.png"));
    } else {
        optionWidget->setHidden(true);
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

void MainWindow::about()
{
    aboutWidget = new AboutWidget();
    aboutWidget->show();
    aboutWidget->setAttribute(Qt::WA_QuitOnClose, false);
}

void MainWindow::openFile()
{
    bool isFirstImageSetup = false;
    QStringList filePaths = QFileDialog::getOpenFileNames(this,
        tr("Open Image"), "D:", tr("Image Files (*.png *.jpg *.bmp)"));
    for (QString filePath : filePaths) {
        QImageReader reader(filePath);
        reader.setAutoTransform(true);
        loadedImage = reader.read();
        if (loadedImage.isNull()) {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                tr("Cannot load %1")
                    .arg(QDir::toNativeSeparators(filePath)));
            return;
        }
        addItemToContainerAndSetPhotoToViewer(loadedImage, filePath, isFirstImageSetup);
    }
}

void MainWindow::addItemToContainerAndSetPhotoToViewer(QImage& image, QString path, bool isFirstImageSetup)
{
    containerWidgetImages->addItemToContainer(image, path);
    if (!isFirstImageSetup) {
        imageViewer->setPhoto(image);
    }
}

void MainWindow::saveFile()
{
    // Think about Global utility function
    QString fileName = QFileDialog::getSaveFileName(this, tr("SaveFile"), "D:", tr("Image Files (*.png *.jpg *.bmp)"));
    QImageWriter writer(fileName);
    if (!writer.write(imageViewer->getPhoto())) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            tr("Cannot write %1: %2")
                .arg(QDir::toNativeSeparators(fileName)),
            writer.errorString());
        return;
    }
}
