#include "optionwidget.h"
#include "imagecontainer.h"
#include "ui_optionwidget.h"

#include <QComboBox>
#include <QDebug>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtMath>

OptionWidget::OptionWidget(ImageViewer* imageViewer, QWidget* parent)
    : instanceOfImageViewer(imageViewer)
    , QTabWidget(parent)
    , ui(new Ui::OptionWidget)
{
    ui->setupUi(this);

    baseTab = new QWidget();
    setupBaseTab();

    openCVTab = new QWidget();
    setupOpenCVTab();

    computerVisionTab = new QWidget();
    setupComputerVisionTab();

    addTab(baseTab, "Base Options");
    addTab(openCVTab, "OpenCV");
    addTab(computerVisionTab, "Computer Vision");

    setTabsEnabled(false);

    connect(fitInViewCheckBox, &QCheckBox::stateChanged, this, &OptionWidget::fitInViewStateChanged);
    connect(editModeCheckBox, &QCheckBox::stateChanged, this, &OptionWidget::editModeEnabler);
    connect(buttonSaveChangesBasicTab, &QPushButton::pressed, this, &OptionWidget::saveChanges);
    connect(buttonSaveChangesOpenCVTab, &QPushButton::pressed, this, &OptionWidget::saveChanges);
    connect(buttonSaveChangesComputerVisionTab, &QPushButton::pressed, this, &OptionWidget::saveChanges);

    connect(cannyEdgeCheckBox, &QCheckBox::stateChanged, this, &OptionWidget::applyEdgeCanny);
    connect(minEdgeSlider, &QSlider::valueChanged, this, &OptionWidget::setMinValueEdge);
    connect(minValueLineEdit, &QLineEdit::editingFinished, this, &OptionWidget::setMinValueEdgeFromLineEdit);
    connect(maxEdgeSlider, &QSlider::valueChanged, this, &OptionWidget::setMaxValueEdge);
    connect(maxValueLineEdit, &QLineEdit::editingFinished, this, &OptionWidget::setMaxValueEdgeFromLineEdit);

    connect(testRotate, &QPushButton::pressed, this, &OptionWidget::applyRotation);
    connect(rotationStyleComboB, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) { chooseRotationStyle(index); });
    connect(acceptRotationFromLineEditButton, &QPushButton::pressed, this, &OptionWidget::rotateFromLineEdit);
    connect(rotationWrappingDial, &QDial::valueChanged, this, &OptionWidget::rotateFromDial);
}

OptionWidget::~OptionWidget()
{
    delete ui;
}

void OptionWidget::setupBaseTab()
{

    auto baseTabLayout = new QVBoxLayout(baseTab);

    buttonSaveChangesBasicTab = new QPushButton("Save Changes");
    buttonSaveChangesBasicTab->setMaximumHeight(maximumSizeOfSaveButton);
    baseTabLayout->addWidget(buttonSaveChangesBasicTab);

    auto baseInfoGBox = new QGroupBox("Basic Information");
    auto baseInfoVLayout = new QVBoxLayout(baseInfoGBox);

    nameOfImage = new QLabel();

    baseInfoVLayout->addWidget(nameOfImage);
    sizeOfImage = new QLabel();
    baseInfoVLayout->addWidget(sizeOfImage);
    pathToImage = new QLabel();
    baseInfoVLayout->addWidget(pathToImage);

    baseTabLayout->addWidget(baseInfoGBox);

    auto baseGeneraGBox = new QGroupBox("General Options");
    auto baseGeneralVLayout = new QVBoxLayout(baseGeneraGBox);

    fitInViewCheckBox = new QCheckBox("Fit in View");
    baseGeneralVLayout->addWidget(fitInViewCheckBox);

    editModeCheckBox = new QCheckBox("Edit Mode");
    baseGeneralVLayout->addWidget(editModeCheckBox);

    buttonOriginalImage = new QPushButton("Original Image Size");
    baseGeneralVLayout->addWidget(buttonOriginalImage);

    baseTabLayout->addWidget(baseGeneraGBox);
}

void OptionWidget::setupOpenCVTab()
{
    openCVOperations = new OpenCVOperations();
    auto openCVTabLayout = new QVBoxLayout(openCVTab);

    buttonSaveChangesOpenCVTab = new QPushButton("Save Changes");
    buttonSaveChangesOpenCVTab->setMaximumHeight(maximumSizeOfSaveButton);
    openCVTabLayout->addWidget(buttonSaveChangesOpenCVTab);

    // Edge Group Box
    auto cannyEdgeGBox = new QGroupBox("Canny Edge Algorithm");
    auto cannyEdgeVBLayout = new QVBoxLayout(cannyEdgeGBox);

    cannyEdgeCheckBox = new QCheckBox("Canny Edge detector");
    cannyEdgeVBLayout->addWidget(cannyEdgeCheckBox);

    // Min Value
    auto minValueHBLayout = new QHBoxLayout();

    int minSizeOfLabels { 15 };
    minValueLabel = new QLabel("0");
    minValueLabel->setMinimumWidth(minSizeOfLabels);
    minValueHBLayout->addWidget(minValueLabel);

    minEdgeSlider = new QSlider(Qt::Orientation::Horizontal);

    minThreshholdEdgeCunny = minValueOfSlider;
    minEdgeSlider->setMinimum(minValueOfSlider);
    minEdgeSlider->setMaximum(maxValueOfSlider);
    minValueLabel->setText(QString::number(minEdgeSlider->value()));
    minValueHBLayout->addWidget(minEdgeSlider);

    minValueLineEdit = new QLineEdit();
    int maxSizeOfLineEdits { 30 };
    minValueLineEdit->setMaximumWidth(maxSizeOfLineEdits);
    minValueHBLayout->addWidget(minValueLineEdit);

    cannyEdgeVBLayout->addLayout(minValueHBLayout);

    // Max Value
    auto maxValueHBLayout = new QHBoxLayout();

    maxValueLabel = new QLabel("100");
    maxValueLabel->setMinimumWidth(minSizeOfLabels);
    maxValueHBLayout->addWidget(maxValueLabel);

    maxEdgeSlider = new QSlider(Qt::Orientation::Horizontal);
    // Following Canny's recomendation highThreshold = LowerThreshold * 3
    maxThreshholdEdgeCunny = minValueOfSlider * 3;
    maxEdgeSlider->setMinimum(minValueOfSlider * 3);
    maxEdgeSlider->setMaximum(maxValueOfSlider * 3);
    maxValueLabel->setText(QString::number(maxEdgeSlider->value()));
    maxValueHBLayout->addWidget(maxEdgeSlider);

    maxValueLineEdit = new QLineEdit();
    maxValueLineEdit->setMaximumWidth(maxSizeOfLineEdits);
    maxValueHBLayout->addWidget(maxValueLineEdit);

    cannyEdgeVBLayout->addLayout(maxValueHBLayout);
    int minSizeOfCannyEdgeGBox { 175 };
    cannyEdgeGBox->setMinimumHeight(minSizeOfCannyEdgeGBox);
    openCVTabLayout->addWidget(cannyEdgeGBox);

    // Rotate Group Box
    testRotate = new QPushButton("Test Rotate");
    openCVTabLayout->addWidget(testRotate);

    auto rotatingGBox = new QGroupBox("Rotating controls");
    auto rotatingVBLayout = new QVBoxLayout(rotatingGBox);

    // Main Controll
    auto rotatingMainControlHBLayout = new QHBoxLayout();
    rotationStyleComboB = new QComboBox();
    rotationStyleComboB->addItem("Dial");
    rotationStyleComboB->addItem("Buttons");

    rotatingMainControlHBLayout->addWidget(rotationStyleComboB);

    rotationLineEdit = new QLineEdit();
    auto rotationLineEditWidth { 35 };
    rotationLineEdit->setMaximumWidth(rotationLineEditWidth);
    rotationLineEdit->setText("0");
    rotatingMainControlHBLayout->addWidget(rotationLineEdit);
    acceptRotationFromLineEditButton = new QPushButton(QIcon(":/mainWindow/acceptIcon.ico"), "");
    auto rotationAcceptButtonWidth { 30 };
    acceptRotationFromLineEditButton->setMaximumWidth(rotationAcceptButtonWidth);
    rotatingMainControlHBLayout->addWidget(acceptRotationFromLineEditButton);
    rotatingVBLayout->addLayout(rotatingMainControlHBLayout);

    //Rotation Control
    // QDial Wrapping
    rotationWrappingDial = new QDial();
    rotationWrappingDial->setWrapping(true);
    auto maxValueofRotationDial { 360 };
    rotationWrappingDial->setMaximum(maxValueofRotationDial);
    rotatingVBLayout->addWidget(rotationWrappingDial);

    // Buttons with step control spin box ?
    rotatingButtonsWidget = new QWidget();
    auto rotatingButtonsVBLayout = new QVBoxLayout(rotatingButtonsWidget);
    auto rotatingButtonsControlHBLayout = new QHBoxLayout();
    rotationButtonLeft = new QPushButton(QIcon(":/mainWindow/rotatingLeftIcon.png"), "");
    auto rotationButtonsMinimumHeight { 75 };
    rotationButtonLeft->setMinimumHeight(rotationButtonsMinimumHeight);
    const QSize defaultButtonIconSize { 75, 75 };
    rotationButtonLeft->setIconSize(defaultButtonIconSize);
    rotatingButtonsControlHBLayout->addWidget(rotationButtonLeft);
    rotationButtonRight = new QPushButton(QIcon(":/mainWindow/rotatingRightIcon.png"), "");
    rotationButtonRight->setMinimumHeight(rotationButtonsMinimumHeight);
    rotationButtonRight->setIconSize(defaultButtonIconSize);
    rotatingButtonsControlHBLayout->addWidget(rotationButtonRight);
    rotatingButtonsVBLayout->addLayout(rotatingButtonsControlHBLayout);
    rotationButtonStepSpinBox = new QSpinBox();
    auto defaultValueOfRotationSpinBox { 5 };
    rotationButtonStepSpinBox->setValue(defaultValueOfRotationSpinBox);
    rotatingButtonsVBLayout->addWidget(rotationButtonStepSpinBox);
    rotatingVBLayout->addWidget(rotatingButtonsWidget);

    // Labels
    auto rotatingValuesLabelsHBLayout = new QHBoxLayout();
    rotationDegreeLabel = new QLabel("0 Degree");
    rotatingValuesLabelsHBLayout->addWidget(rotationDegreeLabel);
    rotationRadiansLabel = new QLabel("0 Radians");
    rotatingValuesLabelsHBLayout->addWidget(rotationRadiansLabel);
    rotatingVBLayout->addLayout(rotatingValuesLabelsHBLayout);

    rotatingButtonsWidget->hide();
    openCVTabLayout->addWidget(rotatingGBox);
}

void OptionWidget::setupComputerVisionTab()
{
    auto computerVisionTabLayout = new QVBoxLayout(computerVisionTab);
    buttonSaveChangesComputerVisionTab = new QPushButton("Save Changes");
    buttonSaveChangesComputerVisionTab->setMaximumHeight(maximumSizeOfSaveButton);
    computerVisionTabLayout->addWidget(buttonSaveChangesComputerVisionTab);
}

Qt::CheckState OptionWidget::getfitInViewCheckBoxState()
{
    return fitInViewCheckBox->checkState();
}

void OptionWidget::updateBaseInformation(QString path)
{
    nameOfImage->setText("Name: " + QFileInfo(path).fileName());
    sizeOfImage->setText("Original size: " + QString::number(instanceOfImageViewer->getPhoto().size().width()) + " x " + QString::number(instanceOfImageViewer->getPhoto().size().height()));
    pathToImage->setText("Path: " + path);
}

void OptionWidget::fitInViewStateChanged()
{
    if (instanceOfImageViewer->hasPhoto()) {
        if (fitInViewCheckBox->checkState() == Qt::CheckState::Checked) {
            instanceOfImageViewer->fitInView(instanceOfImageViewer->getPhotoAsGraphicsPixmapItem());
        } else {
            // Original resolution or diffrent button to do that?
            instanceOfImageViewer->setPhoto(instanceOfImageViewer->getPhoto(), Qt::AspectRatioMode::KeepAspectRatio);
        }
    } else {
        qInfo() << "No photo";
    }
}

void OptionWidget::editModeEnabler()
{
    if (editModeCheckBox->checkState() == Qt::CheckState::Unchecked) {
        setTabsEnabled(false);
    } else {
        setTabsEnabled(true);
    }
}

void OptionWidget::saveChanges()
{
    qInfo() << "Save Changes";
}

void OptionWidget::applyEdgeCanny()
{
    auto originalImage = instanceOfImageViewer->getPhoto();
    openCVOperations->setOriginalPhoto(originalImage);
    if (instanceOfImageViewer->hasPhoto() && cannyEdgeCheckBox->checkState() == Qt::CheckState::Checked) {
        performEdgeDetectionOperation(openCVOperations);
    } else {
        qInfo() << "Canny Edge Unchecked";
        // TODO check Why not working
        instanceOfImageViewer->setPhoto(originalImage, Qt::AspectRatioMode::KeepAspectRatio);
    }
}

void OptionWidget::setMinValueEdge()
{
    minValueLabel->setText(QString::number(minEdgeSlider->value()));
    minThreshholdEdgeCunny = static_cast<double>(minEdgeSlider->value());
}

void OptionWidget::setMinValueEdgeFromLineEdit()
{
    int lowThreshold = minValueLineEdit->text().toInt();
    bool isMinValueInRange = minValueOfSlider < lowThreshold && lowThreshold < maxValueOfSlider;
    if (!minValueLineEdit->text().isEmpty() && isMinValueInRange) {
        minValueLabel->setText(minValueLineEdit->text());
        minThreshholdEdgeCunny = lowThreshold;
        minEdgeSlider->setSliderPosition(lowThreshold);
        minThreshholdEdgeCunny = lowThreshold;
    } else {
        qInfo() << "Min Value Line Edit Empty or out of allowed range";
    }
}

void OptionWidget::setMaxValueEdge()
{
    maxValueLabel->setText(QString::number(maxEdgeSlider->value()));
    maxThreshholdEdgeCunny = static_cast<double>(maxEdgeSlider->value());
}

void OptionWidget::setMaxValueEdgeFromLineEdit()
{
    int highThreshold = maxValueLineEdit->text().toInt();
    // Following Canny's recomendation highThreshold = LowerThreshold * 3
    bool isMaxValueInRange = minValueOfSlider * 3 < highThreshold && highThreshold < maxValueOfSlider * 3;
    if (!maxValueLineEdit->text().isEmpty() && isMaxValueInRange) {
        maxValueLabel->setText(maxValueLineEdit->text());
        maxThreshholdEdgeCunny = highThreshold;
        maxEdgeSlider->setSliderPosition(highThreshold);
        maxThreshholdEdgeCunny = highThreshold;
    } else {
        qInfo() << "Max Value Line Edit Empty or out of allowed range";
    }
}

void OptionWidget::applyRotation()
{
    auto originalPhoto = instanceOfImageViewer->getPhoto();
    openCVOperations->setOriginalPhoto(originalPhoto);
    QImage tempImage = openCVOperations->rotateImageQt(-45);
    instanceOfImageViewer->setPhoto(tempImage, Qt::AspectRatioMode::KeepAspectRatio);
}

void OptionWidget::rotateFromLineEdit()
{
    //qInfo() << rotationLineEdit->text();
    auto angleFromRotationLineEdit = rotationLineEdit->text().toDouble();
    setupRotationLabels(angleFromRotationLineEdit);
    applyRotationToImage(angleFromRotationLineEdit);
}

void OptionWidget::rotateFromDial()
{
    //qInfo() << QString::number(rotationWrappingDial->value());
    rotationLineEdit->setText(QString::number(rotationWrappingDial->value()));
    //applyRotationToImage(static_cast<double>(rotationWrappingDial->value()));
}

void OptionWidget::rotateLeftButton()
{
}

void OptionWidget::rotateRightButton()
{
}

void OptionWidget::performEdgeDetectionOperation(OpenCVOperations* operations)
{
    instanceOfImageViewer->setPhoto(
        operations->cannyEdgeDetectionQt(minThreshholdEdgeCunny, maxThreshholdEdgeCunny),
        Qt::AspectRatioMode::KeepAspectRatio);
}

void OptionWidget::setTabsEnabled(bool enable)
{
    setTabEnabled(tabNameId::OpenCV, enable);
    setTabEnabled(tabNameId::ComputerVision, enable);
}

void OptionWidget::setupRotationLabels(double angle)
{
    rotationDegreeLabel->setText(QString::number(angle) + " Degree");
    rotationRadiansLabel->setText(QString::number(qDegreesToRadians(angle)) + " Radians");
}

void OptionWidget::applyRotationToImage(double angle)
{
    if (instanceOfImageViewer->hasPhoto()) {
        QImage currentPhoto = instanceOfImageViewer->getPhoto();
        openCVOperations->setOriginalPhoto(currentPhoto);
        instanceOfImageViewer->setPhoto(openCVOperations->rotateImageQt(angle), Qt::AspectRatioMode::KeepAspectRatio);
    }
}

void OptionWidget::chooseRotationStyle(int index)
{
    if (index == rotationStyle::Dial) {
        rotationWrappingDial->show();
        rotatingButtonsWidget->hide();
    } else {
        rotationWrappingDial->hide();
        rotatingButtonsWidget->show();
    }
}
