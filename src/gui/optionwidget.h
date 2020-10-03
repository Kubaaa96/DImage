#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include "imageviewer.h"

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
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

private:
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
