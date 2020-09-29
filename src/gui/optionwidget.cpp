#include "optionwidget.h"
#include "ui_optionwidget.h"

OptionWidget::OptionWidget(QWidget* parent)
    : QTabWidget(parent)
    , ui(new Ui::OptionWidget)
{
    ui->setupUi(this);
}

OptionWidget::~OptionWidget()
{
    delete ui;
}
