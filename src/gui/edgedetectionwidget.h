#ifndef EDGEDETECTIONWIDGET_H
#define EDGEDETECTIONWIDGET_H

#include "abstractoperationwidget.h"
#include "imageviewer.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QVBoxLayout>

namespace Ui {
class EdgeDetectionWidget;
}

class EdgeDetectionWidget : public AbstractOperationWidget {
    Q_OBJECT

public:
    explicit EdgeDetectionWidget(ImageViewer* imageViewer, QWidget* parent = nullptr);
    ~EdgeDetectionWidget();
public slots:
    void applyOperation() override;
    void setMinValue();
    void setMinValueFromLineEdit();
    void setMaxValue();
    void setMaxValueFromLineEdit();

private:
    void connectGUIElements();
    ImageViewer* instanceOfImageViewer;

    Ui::EdgeDetectionWidget* ui;

    QVBoxLayout* mainVBLayout;

    QCheckBox* controlCheckBox;
    void setupCheckBox();

    int minWidthOfLabels { 15 };
    QLabel* minValueLabel;
    QSlider* minSlider;
    int minValueOfSlider { 10 };
    int maxValueOfSlider { 60 };
    int maxWidthOfLineEdits { 30 };
    QLineEdit* minLineEdit;
    double minThreshhold;
    void setupMinValue();

    QLabel* maxValueLabel;
    QSlider* maxSlider;
    QLineEdit* maxLineEdit;
    double maxThreshhold;
    void setupMaxValue();
};

#endif // EDGEDETECTIONWIDGET_H
