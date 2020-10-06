#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include "../app/openCVOperations.h"
#include "imageviewer.h"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QTabWidget>

namespace Ui {
class OptionWidget;
}

class OptionWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit OptionWidget(ImageViewer* imageViewer, QWidget* parent = nullptr);
    ~OptionWidget();
    Qt::CheckState getfitInViewCheckBoxState();
    void updateBaseInformation(QString path);

public slots:
    void fitInViewStateChanged();
    void editModeEnabler();
    void saveChanges();
    void applyEdgeCanny();
    void setMinValueEdge();
    void setMinValueEdgeFromLineEdit();
    void setMaxValueEdge();
    void setMaxValueEdgeFromLineEdit();
    void applyRotation();

private:
    OpenCVOperations* openCVOperations;
    void performEdgeDetectionOperation(OpenCVOperations* operations);

    void setTabsEnabled(bool enable);

    Ui::OptionWidget* ui;

    QWidget* baseTab;
    QWidget* openCVTab;
    QWidget* computerVisionTab;

    class ImageViewer* instanceOfImageViewer;

    QCheckBox* fitInViewCheckBox;
    QCheckBox* editModeCheckBox;
    QPushButton* buttonOriginalImage;
    const int maximumSizeOfSaveButton { 30 };
    QPushButton* buttonSaveChangesBasicTab;
    QPushButton* buttonSaveChangesOpenCVTab;
    QPushButton* buttonSaveChangesComputerVisionTab;

    // OpenCV Operation
    //Edge Detection
    QCheckBox* cannyEdgeCheckBox;
    QLabel* minValueLabel;
    QSlider* minEdgeSlider;
    int minValueOfSlider { 10 };
    int maxValueOfSlider { 60 };
    QLineEdit* minValueLineEdit;
    double minThreshholdEdgeCunny;

    QLabel* maxValueLabel;
    QSlider* maxEdgeSlider;
    QLineEdit* maxValueLineEdit;
    double maxThreshholdEdgeCunny;

    // Image Rotation Two Buttons with arrows or circle slider
    QPushButton* testRotate;
    QComboBox* rotationStyleComboB;
    QLabel* rotationDegreeLabel;
    QLabel* rotationRadiansLabel;
    QLineEdit* rotationLineEdit;
    QPushButton* acceptRotationFromLineEditButton;

    // Image Translation Matrix of translation? Dragable Contours of image or corners?
    // Adaptive Threshgholding Slider + Push Button
    // Basic Image Segmentation Button
    // BitWise Operation Separate Small group box?
    // Smoothing Images Separate Group Box
    // Image Contours Push Button
    // SIFT Button and maybe line edit
    // SURF Button and maybe line edit

    QLabel* nameOfImage;
    QLabel* sizeOfImage;
    QLabel* pathToImage;

    void setupBaseTab();
    void setupOpenCVTab();
    void setupComputerVisionTab();

    enum tabNameId {
        Base,
        OpenCV,
        ComputerVision
    };
};

#endif // OPTIONWIDGET_H
