#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H
#include "../app/openCVOperations.h"
#include "edgedetectionwidget.h"
#include "imagerotationwidget.h"
#include "imageviewer.h"

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

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

private:
    OpenCVOperations* openCVOperations;

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

    ImageRotationWidget* imageRotationWidget;

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

    bool isCheckBoxChecked(QCheckBox* checkBox);

    enum tabNameId {
        Base,
        OpenCV,
        ComputerVision
    };
};

#endif // OPTIONWIDGET_H
