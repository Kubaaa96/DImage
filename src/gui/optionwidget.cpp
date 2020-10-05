#include "optionwidget.h"
#include "../app/openCVOperations.h"
#include "ui_optionwidget.h"

#include <QDebug>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSlider>
#include <QVBoxLayout>

OptionWidget::OptionWidget(ImageViewer* imageViewer, QWidget* parent)
    : instanceOfImageViewer(imageViewer)
    , QTabWidget(parent)
    , ui(new Ui::OptionWidget)
{
    ui->setupUi(this);

    baseTab = new QWidget();
    setupBaseTab();

    openCVTab = new QWidget();
    setupOpenCVTab();

    computerVisionTab = new QWidget();
    setupComputerVisionTab();

    addTab(baseTab, "Base Options");
    addTab(openCVTab, "OpenCV");
    addTab(computerVisionTab, "Computer Vision");

    connect(fitInViewCheckBox, &QCheckBox::stateChanged, this, &OptionWidget::fitInViewStateChanged);
    connect(editModeCheckBox, &QCheckBox::stateChanged, this, &OptionWidget::editModeEnabler);
    connect(buttonSaveChangesBasicTab, &QPushButton::pressed, this, &OptionWidget::saveChanges);
    connect(buttonSaveChangesOpenCVTab, &QPushButton::pressed, this, &OptionWidget::saveChanges);
    connect(buttonSaveChangesComputerVisionTab, &QPushButton::pressed, this, &OptionWidget::saveChanges);

    connect(cannyEdgeCheckBox, &QCheckBox::stateChanged, this, &OptionWidget::applyEdgeCanny);
}

OptionWidget::~OptionWidget()
{
    delete ui;
}

void OptionWidget::setupBaseTab()
{

    auto baseTabLayout = new QVBoxLayout(baseTab);

    buttonSaveChangesBasicTab = new QPushButton("Save Changes");
    buttonSaveChangesBasicTab->setMaximumHeight(maximumSizeOfSaveButton);
    baseTabLayout->addWidget(buttonSaveChangesBasicTab);

    auto baseInfoGBox = new QGroupBox("Basic Information");
    auto baseInfoVLayout = new QVBoxLayout(baseInfoGBox);

    nameOfImage = new QLabel();

    baseInfoVLayout->addWidget(nameOfImage);
    sizeOfImage = new QLabel();
    baseInfoVLayout->addWidget(sizeOfImage);
    pathToImage = new QLabel();
    baseInfoVLayout->addWidget(pathToImage);

    baseTabLayout->addWidget(baseInfoGBox);

    auto baseGeneraGBox = new QGroupBox("General Options");
    auto baseGeneralVLayout = new QVBoxLayout(baseGeneraGBox);

    fitInViewCheckBox = new QCheckBox("Fit in View");
    baseGeneralVLayout->addWidget(fitInViewCheckBox);

    editModeCheckBox = new QCheckBox("Edit Mode");
    baseGeneralVLayout->addWidget(editModeCheckBox);

    buttonOriginalImage = new QPushButton("Original Image Size");
    baseGeneralVLayout->addWidget(buttonOriginalImage);

    baseTabLayout->addWidget(baseGeneraGBox);
}

void OptionWidget::setupOpenCVTab()
{
    auto openCVTabLayout = new QVBoxLayout(openCVTab);

    buttonSaveChangesOpenCVTab = new QPushButton("Save Changes");
    buttonSaveChangesOpenCVTab->setMaximumHeight(maximumSizeOfSaveButton);
    openCVTabLayout->addWidget(buttonSaveChangesOpenCVTab);

    // Edge Group Box
    auto cannyEdgeGBox = new QGroupBox("Canny Edge Algorithm");
    auto cannyEdgeVBLayout = new QVBoxLayout(cannyEdgeGBox);

    cannyEdgeCheckBox = new QCheckBox("Canny Edge detector");
    cannyEdgeVBLayout->addWidget(cannyEdgeCheckBox);

    // Min Value
    auto minValueHBLayout = new QHBoxLayout();

    auto minValueLabel = new QLabel("0");
    minValueHBLayout->addWidget(minValueLabel);
    //TODO Think about separators to give more space for label
    auto minEdgeSlider = new QSlider(Qt::Orientation::Horizontal);
    minValueHBLayout->addWidget(minEdgeSlider);

    auto minValueLineEdit = new QLineEdit();
    // TODO get rid of magic numbers
    minValueLineEdit->setMaximumWidth(30);
    minValueHBLayout->addWidget(minValueLineEdit);

    cannyEdgeVBLayout->addLayout(minValueHBLayout);

    // Max Value
    auto maxValueHBLayout = new QHBoxLayout();

    auto maxValueLabel = new QLabel("100");
    maxValueHBLayout->addWidget(maxValueLabel);

    auto maxEdgeSlider = new QSlider(Qt::Orientation::Horizontal);
    maxValueHBLayout->addWidget(maxEdgeSlider);
    cannyEdgeVBLayout->addLayout(maxValueHBLayout);

    auto maxValueLineEdit = new QLineEdit();
    // TODO get rid of magic numbers
    maxValueLineEdit->setMaximumWidth(30);
    maxValueHBLayout->addWidget(maxValueLineEdit);

    openCVTabLayout->addWidget(cannyEdgeGBox);
    // TODO get rid of magic numbers
    cannyEdgeGBox->setMinimumHeight(175);
}

void OptionWidget::setupComputerVisionTab()
{
    auto computerVisionTabLayout = new QVBoxLayout(computerVisionTab);
    buttonSaveChangesComputerVisionTab = new QPushButton("Save Changes");
    buttonSaveChangesComputerVisionTab->setMaximumHeight(maximumSizeOfSaveButton);
    computerVisionTabLayout->addWidget(buttonSaveChangesComputerVisionTab);
}

Qt::CheckState OptionWidget::getfitInViewCheckBoxState()
{
    return fitInViewCheckBox->checkState();
}

void OptionWidget::updateBaseInformation(QString path)
{
    nameOfImage->setText("Name: " + QFileInfo(path).fileName());
    sizeOfImage->setText("Original size: " + QString::number(instanceOfImageViewer->getPhoto().size().width()) + " x " + QString::number(instanceOfImageViewer->getPhoto().size().height()));
    pathToImage->setText("Path: " + path);
}

void OptionWidget::fitInViewStateChanged()
{
    if (instanceOfImageViewer->hasPhoto()) {
        if (fitInViewCheckBox->checkState() == Qt::CheckState::Checked) {
            instanceOfImageViewer->fitInView(instanceOfImageViewer->getPhotoAsGraphicsPixmapItem());
        } else {
            // Original resolution or separate button to do that?
            instanceOfImageViewer->setPhoto(instanceOfImageViewer->getPhoto(), Qt::AspectRatioMode::KeepAspectRatio);
        }
    } else {
        qInfo() << "No photo";
    }
}

void OptionWidget::editModeEnabler()
{
    if (editModeCheckBox->checkState() == Qt::CheckState::Checked) {
        setTabEnabled(tabNameId::OpenCV, false);
        setTabEnabled(tabNameId::ComputerVision, false);
    } else {
        setTabEnabled(tabNameId::OpenCV, true);
        setTabEnabled(tabNameId::ComputerVision, true);
    }
}

void OptionWidget::saveChanges()
{
    qInfo() << "Save Changes";
}

void OptionWidget::applyEdgeCanny()
{
    if (instanceOfImageViewer->hasPhoto() && cannyEdgeCheckBox->checkState() == Qt::CheckState::Checked) {
        auto openCVOperations = new OpenCVOperations(instanceOfImageViewer->getPhoto());
        QImage image = openCVOperations->cannyEdgeDetectionQ(20, 50);
        //openCVOperations->cannyEdgeDetection(20, 50);
        instanceOfImageViewer->setPhoto(image, Qt::AspectRatioMode::IgnoreAspectRatio);
        //printf(instanceOfImageViewer->hasPhoto() ? "true" : "false");
    } else {
        qInfo() << "Canny Edge Unchecked";
    }
}
