#include "optionwidget.h"
#include "ui_optionwidget.h"

OptionWidget::OptionWidget(QWidget* parent)
    : QTabWidget(parent)
    , ui(new Ui::OptionWidget)
{
    ui->setupUi(this);

    baseTab = new QWidget();
    openCVTab = new QWidget();
    computerVisionTab = new QWidget();

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
}

void OptionWidget::setupOpenCVTab()
{
}

void OptionWidget::setupComputerVisionTab()
{
}
