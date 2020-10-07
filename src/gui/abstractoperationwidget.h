#ifndef ABSTRACTOPERATIONWIDGET_H
#define ABSTRACTOPERATIONWIDGET_H

#include "../app/openCVOperations.h"
#include <QGroupBox>

class AbstractOperationWidget : public QGroupBox {
    Q_OBJECT

public:
    explicit AbstractOperationWidget(QWidget* parent = nullptr);
    ~AbstractOperationWidget();
public slots:
    virtual void applyOperation() = 0;

protected:
    OpenCVOperations* openCVOperations;

private:
    int minHeightOfGroupBox { 175 };
};

#endif // ABSTRACTOPERATIONWIDGET_H
