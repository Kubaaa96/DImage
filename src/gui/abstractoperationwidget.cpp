#include "abstractoperationwidget.h"

AbstractOperationWidget::AbstractOperationWidget(QWidget* parent)
    : QGroupBox(parent)
{
    openCVOperations = new OpenCVOperations();
    setMinimumHeight(minHeightOfGroupBox);
}

AbstractOperationWidget::~AbstractOperationWidget()
{
}
