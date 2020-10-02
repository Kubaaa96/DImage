#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include "imageviewer.h"

#include <QCheckBox>
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

public slots:
    void fitInViewStateChanged();
    void editModeEnabler();

private:
    Ui::OptionWidget* ui;

    QWidget* baseTab;
    QWidget* openCVTab;
    QWidget* computerVisionTab;

    class ImageViewer* instanceOfImageViewer;

    QCheckBox* fitInViewCheckBox;
    QCheckBox* editModeCheckBox;
    QPushButton* buttonOriginalImage;

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
