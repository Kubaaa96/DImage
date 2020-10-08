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
    delete radiansLabel;
    delete degreeLabel;
    delete buttonStepSpinBox;
    delete buttonRight;
    delete buttonLeft;
    delete buttonsWidget;
    delete dial;
    delete acceptFromLineEditButton;
    delete denominatorRadiansLineEdit;
    delete numeratorRadiansLineEdit;
    delete radianFractionRadioButton;
    delete radianLineEdit;
    delete radianRadioButton;
    delete lineEdit;
}

void ImageRotationWidget::applyOperation()
{

    auto angleFromRotationLineEdit = lineEdit->text().toDouble();
    // auto angleFromRotationLineEdit = getAngleFromLineEdits();
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

void ImageRotationWidget::radiansRadioButton()
{
    dissableFractialradianLineEdits();
}
void ImageRotationWidget::radiansFractialRadioButton()
{
    radianLineEdit->setEnabled(false);
    radianRadioButton->setChecked(false);
    if (!numeratorRadiansLineEdit->isEnabled() && !denominatorRadiansLineEdit->isEnabled()) {
        numeratorRadiansLineEdit->setEnabled(true);
        denominatorRadiansLineEdit->setEnabled(true);
    }
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
    connect(radianRadioButton, &QRadioButton::clicked, this, &ImageRotationWidget::radiansRadioButton);
    connect(radianFractionRadioButton, &QRadioButton::clicked, this, &ImageRotationWidget::radiansFractialRadioButton);
}

void ImageRotationWidget::setupMainControl()
{
    auto controlVBlayout = new QVBoxLayout();
    auto comboBoxesHBLayout = new QHBoxLayout();
    controlComboBox = new QComboBox();
    controlComboBox->addItem("Dial");
    controlComboBox->addItem("Buttons");
    comboBoxesHBLayout->addWidget(controlComboBox);

    unitControllComboBox = new QComboBox();
    unitControllComboBox->addItem("Degrees");
    unitControllComboBox->addItem("Radians");
    comboBoxesHBLayout->addWidget(unitControllComboBox);
    controlVBlayout->addLayout(comboBoxesHBLayout);

    auto lineEditsHBLayout = new QHBoxLayout();

    lineEdit = new QLineEdit();
    lineEdit->setMaximumWidth(lineEditDegreeWidth);
    lineEdit->setText("0");
    lineEditsHBLayout->addWidget(lineEdit);

    radiansLineEdits = new QWidget();
    auto radiansVBLayout = new QVBoxLayout(radiansLineEdits);

    radianLineEditWidget = new QWidget();
    auto radiansHBLayout = new QHBoxLayout(radianLineEditWidget);
    radianRadioButton = new QRadioButton();
    radiansHBLayout->addWidget(radianRadioButton);
    radianLineEdit = new QLineEdit();
    radiansHBLayout->addWidget(radianLineEdit);
    radiansVBLayout->addWidget(radianLineEditWidget);

    radiansPILineEdits = new QWidget();
    auto radiansPIHBLayout = new QHBoxLayout(radiansPILineEdits);
    radianFractionRadioButton = new QRadioButton();
    radiansPIHBLayout->addWidget(radianFractionRadioButton);
    numeratorRadiansLineEdit = new QLineEdit();
    radiansPIHBLayout->addWidget(numeratorRadiansLineEdit);
    const QChar MathSymbolPi(0x03C0);
    auto piLabel = new QLabel(QString(MathSymbolPi) + "/");
    radiansPIHBLayout->addWidget(piLabel);
    denominatorRadiansLineEdit = new QLineEdit();
    radiansPIHBLayout->addWidget(denominatorRadiansLineEdit);
    radiansVBLayout->addWidget(radiansPILineEdits);
    lineEditsHBLayout->addWidget(radiansLineEdits);
    radiansLineEdits->setMaximumHeight(maxRadiansLineEdits);
    radiansLineEdits->hide();
    dissableFractialradianLineEdits();
    radianRadioButton->setChecked(true);

    acceptFromLineEditButton = new QPushButton(QIcon(":/mainWindow/acceptIcon.ico"), "");
    acceptFromLineEditButton->setMaximumWidth(acceptButtonWidth);
    lineEditsHBLayout->addWidget(acceptFromLineEditButton);
    controlVBlayout->addLayout(lineEditsHBLayout);
    mainVBLayout->addLayout(controlVBlayout);
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

double ImageRotationWidget::getAngleFromLineEdits()
{
    return 0.0;
}

void ImageRotationWidget::dissableFractialradianLineEdits()
{
    numeratorRadiansLineEdit->setEnabled(false);
    denominatorRadiansLineEdit->setEnabled(false);
    radianFractionRadioButton->setChecked(false);
    if (!radianLineEdit->isEnabled()) {
        radianLineEdit->setEnabled(true);
        radianRadioButton->setChecked(true);
    }
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
        lineEdit->show();
        radiansLineEdits->hide();
    } else {
        currentUnit = RotationUnits::Radians;
        radiansLineEdits->show();
        lineEdit->hide();
    }
}
