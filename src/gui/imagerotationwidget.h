#ifndef IMAGEROTATIONWIDGET_H
#define IMAGEROTATIONWIDGET_H

#include "abstractoperationwidget.h"
#include "imageviewer.h"

#include <QComboBox>
#include <QDial>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

namespace Ui {
class ImageRotationWidget;
}

class ImageRotationWidget : public AbstractOperationWidget {
    Q_OBJECT

public:
    explicit ImageRotationWidget(ImageViewer* imageViewer, QWidget* parent = nullptr);
    ~ImageRotationWidget();
public slots:
    void applyOperation() override;
    void rotateFromDial();
    void rotateLeftButton();
    void rotateRightButton();

private:
    enum class RotationStyle {
        Dial,
        Buttons
    };

    enum class RotationUnits {
        Degrees,
        Radians
    };

    void connectGUIElements();
    ImageViewer* instanceOfImageViewer;

    Ui::ImageRotationWidget* ui;

    QVBoxLayout* mainVBLayout;

    QComboBox* controlComboBox;
    QComboBox* unitControllComboBox;
    int lineEditWidth { 35 };
    QLineEdit* lineEdit;
    int acceptButtonWidth { 30 };
    QPushButton* acceptFromLineEditButton;
    void setupMainControl();

    int maxRotationValueOfDial { 360 };
    QDial* dial;
    void setupDial();

    QWidget* buttonsWidget;
    int rotationButtonsMinHeight { 75 };
    const QSize defaultButtonsIconSize { 75, 75 };
    QPushButton* buttonLeft;
    QPushButton* buttonRight;
    int defaultValueOfSpinBox { 5 };
    QSpinBox* buttonStepSpinBox;
    void setupControllButtons();

    QLabel* degreeLabel;
    QLabel* radiansLabel;
    void setupGUILabels();

    double radians = 0.0;
    double degrees = 0.0;
    void setupRotationValues(double value);
    void setupRotationLabels(double value);
    void applyRotationToImage(double value);
    void chooseRotationStyle(int index);
    void chooseUnit(int index);
    RotationUnits currentUnit { RotationUnits::Degrees };
};

#endif // IMAGEROTATIONWIDGET_H
