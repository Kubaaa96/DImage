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
    void connectGUIElements();
    ImageViewer* instanceOfImageViewer;

    Ui::ImageRotationWidget* ui;

    QVBoxLayout* mainVBLayout;

    QComboBox* controlComboBox;
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

    void setupRotationLabels(double angle);
    void applyRotationToImage(double angle);
    void chooseRotationStyle(int index);

    enum class rotationStyle {
        Dial,
        Buttons
    };
};

#endif // IMAGEROTATIONWIDGET_H
