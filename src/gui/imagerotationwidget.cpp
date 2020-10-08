#include "imagerotationwidget.h"
#include "../util/dimageutility.h"
#include "ui_imagerotationwidget.h"

#include <QHBoxLayout>
#include <QtMath>

ImageRotationWidget::ImageRotationWidget(ImageViewer* imageViewer, QWidget* parent)
    : instanceOfImageViewer(imageViewer)
    , AbstractOperationWidget(parent)
    , ui(new Ui::ImageRotationWidget)
{
    ui->setupUi(this);
    mainVBLayout = new QVBoxLayout(this);
    setupMainControl();
    setupDial();
    setupControllButtons();
    setupGUILabels();
    connectGUIElements();
    // Default setup of Dial on top
    buttonsWidget->hide();
}

ImageRotationWidget::~ImageRotationWidget()
{
    delete ui;
}

void ImageRotationWidget::applyOperation()
{
    auto angleFromRotationLineEdit = lineEdit->text().toDouble();
    setupRotationLabels(angleFromRotationLineEdit);
    applyRotationToImage(angleFromRotationLineEdit);
}

void ImageRotationWidget::rotateFromDial()
{
    lineEdit->setText(QString::number(dial->value()));
}

void ImageRotationWidget::rotateLeftButton()
{
    applyRotationToImage(-buttonStepSpinBox->value());
}

void ImageRotationWidget::rotateRightButton()
{
    applyRotationToImage(buttonStepSpinBox->value());
}

void ImageRotationWidget::connectGUIElements()
{
    connect(controlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) { chooseRotationStyle(index); });
    connect(unitControllComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) { chooseUnit(index); });
    connect(acceptFromLineEditButton, &QPushButton::pressed, this, &ImageRotationWidget::applyOperation);
    connect(dial, &QDial::valueChanged, this, &ImageRotationWidget::rotateFromDial);
    connect(buttonLeft, &QPushButton::pressed, this, &ImageRotationWidget::rotateLeftButton);
    connect(buttonRight, &QPushButton::pressed, this, &ImageRotationWidget::rotateRightButton);
}

void ImageRotationWidget::setupMainControl()
{
    auto HBLayout = new QHBoxLayout();
    controlComboBox = new QComboBox();
    controlComboBox->addItem("Dial");
    controlComboBox->addItem("Buttons");
    HBLayout->addWidget(controlComboBox);

    unitControllComboBox = new QComboBox();
    unitControllComboBox->addItem("Degrees");
    unitControllComboBox->addItem("Radians");
    HBLayout->addWidget(unitControllComboBox);

    lineEdit = new QLineEdit();
    lineEdit->setMaximumWidth(lineEditWidth);
    lineEdit->setText("0");
    HBLayout->addWidget(lineEdit);

    acceptFromLineEditButton = new QPushButton(QIcon(":/mainWindow/acceptIcon.ico"), "");
    acceptFromLineEditButton->setMaximumWidth(acceptButtonWidth);
    HBLayout->addWidget(acceptFromLineEditButton);
    mainVBLayout->addLayout(HBLayout);
}

void ImageRotationWidget::setupDial()
{
    dial = new QDial();
    dial->setWrapping(true);
    dial->setMaximum(maxRotationValueOfDial);
    mainVBLayout->addWidget(dial);
}

void ImageRotationWidget::setupControllButtons()
{
    buttonsWidget = new QWidget();

    auto VBLayout = new QVBoxLayout(buttonsWidget);

    auto buttonsHBLayout = new QHBoxLayout();

    buttonLeft = new QPushButton(QIcon(":/mainWindow/rotatingLeftIcon.png"), "");
    buttonLeft->setMinimumHeight(rotationButtonsMinHeight);
    buttonLeft->setIconSize(defaultButtonsIconSize);
    buttonsHBLayout->addWidget(buttonLeft);

    buttonRight = new QPushButton(QIcon(":/mainWindow/rotatingRightIcon.png"), "");
    buttonRight->setMinimumHeight(rotationButtonsMinHeight);
    buttonRight->setIconSize(defaultButtonsIconSize);
    buttonsHBLayout->addWidget(buttonRight);
    VBLayout->addLayout(buttonsHBLayout);

    buttonStepSpinBox = new QSpinBox();
    buttonStepSpinBox->setValue(defaultValueOfSpinBox);
    VBLayout->addWidget(buttonStepSpinBox);
    mainVBLayout->addWidget(buttonsWidget);
}

void ImageRotationWidget::setupGUILabels()
{
    auto HBLayout = new QHBoxLayout();
    degreeLabel = new QLabel("0 Degree");
    HBLayout->addWidget(degreeLabel);

    radiansLabel = new QLabel("0 Radians");
    HBLayout->addWidget(radiansLabel);
    mainVBLayout->addLayout(HBLayout);
}

void ImageRotationWidget::setupRotationValues(double value)
{
    if (currentUnit == RotationUnits::Degrees) {
        degrees = value;
        radians = qDegreesToRadians(value);
    } else {
        radians = value;
        degrees = qRadiansToDegrees(value);
    }
}

void ImageRotationWidget::setupRotationLabels(double value)
{
    setupRotationValues(value);
    degreeLabel->setText(QString::number(degrees) + " Degree");
    radiansLabel->setText(QString::number(radians) + " Radians");
}

void ImageRotationWidget::applyRotationToImage(double value)
{
    setupRotationValues(value);
    if (instanceOfImageViewer->hasPhoto()) {
        QImage currentPhoto = instanceOfImageViewer->getPhoto();
        openCVOperations->setOriginalPhoto(currentPhoto);
        instanceOfImageViewer->setPhoto(openCVOperations->rotateImageQt(degrees), Qt::AspectRatioMode::KeepAspectRatio);
    }
}

void ImageRotationWidget::chooseRotationStyle(int index)
{
    if (index == DImageUtil::as_integer(RotationStyle::Dial)) {
        dial->show();
        buttonsWidget->hide();
    } else {
        dial->hide();
        buttonsWidget->show();
    }
}

void ImageRotationWidget::chooseUnit(int index)
{
    if (index == DImageUtil::as_integer(RotationUnits::Degrees)) {
        currentUnit = RotationUnits::Degrees;
    } else {
        currentUnit = RotationUnits::Radians;
    }
}
