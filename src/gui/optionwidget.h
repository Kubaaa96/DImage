#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H
#include "../app/openCVOperations.h"
#include "edgedetectionwidget.h"
#include "imageviewer.h"

#include <QCheckBox>
#include <QDial>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
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

    // Rotation Slots

    void rotateFromLineEdit();
    void rotateFromDial();
    void rotateLeftButton();
    void rotateRightButton();

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
    EdgeDetectionWidget* edgeDetectionWidget;
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
    QComboBox* rotationStyleComboB;
    QLabel* rotationDegreeLabel;
    QLabel* rotationRadiansLabel;
    QLineEdit* rotationLineEdit;
    QPushButton* rotationAcceptFromLineEditButton;
    QDial* rotationWrappingDial;
    QWidget* rotationButtonsWidget;
    QPushButton* rotationButtonLeft;
    QPushButton* rotationButtonRight;
    QSpinBox* rotationButtonStepSpinBox;

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

    void setupRotationLabels(double angle);
    void applyRotationToImage(double angle);
    void chooseRotationStyle(int index);

    enum tabNameId {
        Base,
        OpenCV,
        ComputerVision
    };
    enum rotationStyle {
        Dial,
        Buttons
    };
};

#endif // OPTIONWIDGET_H
