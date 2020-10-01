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
}

OptionWidget::~OptionWidget()
{
    delete ui;
}

void OptionWidget::setupBaseTab()
{
    QVBoxLayout* baseTabLayout = new QVBoxLayout(baseTab);

    QGroupBox* baseInfoGBox = new QGroupBox("Basic Information");
    baseTabLayout->addWidget(baseInfoGBox);

    QGroupBox* baseGeneraGBox = new QGroupBox("General Options");

    QVBoxLayout* baseGeneralVLayout = new QVBoxLayout(baseGeneraGBox);
    fitInViewCheckBox = new QCheckBox("Fit in View");
    baseGeneralVLayout->addWidget(fitInViewCheckBox);

    baseTabLayout->addWidget(baseGeneraGBox);
}

void OptionWidget::setupOpenCVTab()
{
}

void OptionWidget::setupComputerVisionTab()
{
}

void OptionWidget::fitInViewStateChanged()
{
    if (instanceOfImageViewer->hasPhoto()) {
        if (fitInViewCheckBox->checkState() == Qt::CheckState::Checked) {
            qInfo() << "Fit in View Check box CHECKED";
            instanceOfImageViewer->fitInView(instanceOfImageViewer->getPhotoAsGraphicsPixmapItem());
        } else {
            // Original resolution or separate button to do that?
            qInfo() << "Fit in view UNCHECKED";
        }
    } else {
        qInfo() << "No photo";
    }
}
