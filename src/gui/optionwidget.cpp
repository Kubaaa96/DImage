#include "optionwidget.h"
#include "ui_optionwidget.h"

#include <QDebug>
#include <QGroupBox>
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
}

OptionWidget::~OptionWidget()
{
    delete ui;
}

void OptionWidget::setupBaseTab()
{
    auto baseTabLayout = new QVBoxLayout(baseTab);

    auto baseInfoGBox = new QGroupBox("Basic Information");
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
}

void OptionWidget::setupComputerVisionTab()
{
}

Qt::CheckState OptionWidget::getfitInViewCheckBoxState()
{
    return fitInViewCheckBox->checkState();
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
