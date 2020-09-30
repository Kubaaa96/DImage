#include "optionwidget.h"
#include "ui_optionwidget.h"

#include <QGroupBox>
#include <QVBoxLayout>

OptionWidget::OptionWidget(QWidget* parent)
    : QTabWidget(parent)
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
    baseTabLayout->addWidget(baseGeneraGBox);
}

void OptionWidget::setupOpenCVTab()
{
}

void OptionWidget::setupComputerVisionTab()
{
}
