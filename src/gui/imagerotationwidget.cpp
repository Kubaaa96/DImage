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
}

void ImageRotationWidget::rotateFromLineEdit()
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
    connect(acceptFromLineEditButton, &QPushButton::pressed, this, &ImageRotationWidget::rotateFromLineEdit);
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

void ImageRotationWidget::setupRotationLabels(double angle)
{
    degreeLabel->setText(QString::number(angle) + " Degree");
    radiansLabel->setText(QString::number(qDegreesToRadians(angle)) + " Radians");
}

void ImageRotationWidget::applyRotationToImage(double angle)
{
    if (instanceOfImageViewer->hasPhoto()) {
        QImage currentPhoto = instanceOfImageViewer->getPhoto();
        openCVOperations->setOriginalPhoto(currentPhoto);
        instanceOfImageViewer->setPhoto(openCVOperations->rotateImageQt(angle), Qt::AspectRatioMode::KeepAspectRatio);
    }
}

void ImageRotationWidget::chooseRotationStyle(int index)
{
    if (index == DImageUtil::as_integer(rotationStyle::Dial)) {
        dial->show();
        buttonsWidget->hide();
    } else {
        dial->hide();
        buttonsWidget->show();
    }
}
