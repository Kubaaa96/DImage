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

#include <functional>

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

    connect(rotationStyleComboB, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) { chooseRotationStyle(index); });
    connect(rotationAcceptFromLineEditButton, &QPushButton::pressed, this, &OptionWidget::rotateFromLineEdit);
    connect(rotationWrappingDial, &QDial::valueChanged, this, &OptionWidget::rotateFromDial);
    connect(rotationButtonLeft, &QPushButton::pressed, this, &OptionWidget::rotateLeftButton);
    connect(rotationButtonRight, &QPushButton::pressed, this, &OptionWidget::rotateRightButton);
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

    edgeDetectionWidget = new EdgeDetectionWidget(instanceOfImageViewer);
    openCVTabLayout->addWidget(edgeDetectionWidget);

    // Rotate Group Box
    auto rotationGBox = new QGroupBox("Rotating controls");
    auto rotationVBLayout = new QVBoxLayout(rotationGBox);

    // Main Controll
    auto rotationMainControlHBLayout = new QHBoxLayout();
    rotationStyleComboB = new QComboBox();
    rotationStyleComboB->addItem("Dial");
    rotationStyleComboB->addItem("Buttons");

    rotationMainControlHBLayout->addWidget(rotationStyleComboB);

    rotationLineEdit = new QLineEdit();
    auto rotationLineEditWidth { 35 };
    rotationLineEdit->setMaximumWidth(rotationLineEditWidth);
    rotationLineEdit->setText("0");
    rotationMainControlHBLayout->addWidget(rotationLineEdit);
    rotationAcceptFromLineEditButton = new QPushButton(QIcon(":/mainWindow/acceptIcon.ico"), "");
    auto rotationAcceptButtonWidth { 30 };
    rotationAcceptFromLineEditButton->setMaximumWidth(rotationAcceptButtonWidth);
    rotationMainControlHBLayout->addWidget(rotationAcceptFromLineEditButton);
    rotationVBLayout->addLayout(rotationMainControlHBLayout);

    //Rotation Control
    // QDial Wrapping
    rotationWrappingDial = new QDial();
    rotationWrappingDial->setWrapping(true);
    auto maxValueofRotationDial { 360 };
    rotationWrappingDial->setMaximum(maxValueofRotationDial);
    rotationVBLayout->addWidget(rotationWrappingDial);

    // Buttons with step control spin box ?
    rotationButtonsWidget = new QWidget();
    auto rotationButtonsVBLayout = new QVBoxLayout(rotationButtonsWidget);
    auto rotationButtonsControlHBLayout = new QHBoxLayout();
    rotationButtonLeft = new QPushButton(QIcon(":/mainWindow/rotatingLeftIcon.png"), "");
    auto rotationButtonsMinimumHeight { 75 };
    rotationButtonLeft->setMinimumHeight(rotationButtonsMinimumHeight);
    const QSize defaultButtonIconSize { 75, 75 };
    rotationButtonLeft->setIconSize(defaultButtonIconSize);
    rotationButtonsControlHBLayout->addWidget(rotationButtonLeft);
    rotationButtonRight = new QPushButton(QIcon(":/mainWindow/rotatingRightIcon.png"), "");
    rotationButtonRight->setMinimumHeight(rotationButtonsMinimumHeight);
    rotationButtonRight->setIconSize(defaultButtonIconSize);
    rotationButtonsControlHBLayout->addWidget(rotationButtonRight);
    rotationButtonsVBLayout->addLayout(rotationButtonsControlHBLayout);
    rotationButtonStepSpinBox = new QSpinBox();
    auto defaultValueOfRotationSpinBox { 5 };
    rotationButtonStepSpinBox->setValue(defaultValueOfRotationSpinBox);
    rotationButtonsVBLayout->addWidget(rotationButtonStepSpinBox);
    rotationVBLayout->addWidget(rotationButtonsWidget);

    // Labels
    auto rotationValuesLabelsHBLayout = new QHBoxLayout();
    rotationDegreeLabel = new QLabel("0 Degree");
    rotationValuesLabelsHBLayout->addWidget(rotationDegreeLabel);
    rotationRadiansLabel = new QLabel("0 Radians");
    rotationValuesLabelsHBLayout->addWidget(rotationRadiansLabel);
    rotationVBLayout->addLayout(rotationValuesLabelsHBLayout);
    rotationButtonsWidget->hide();
    openCVTabLayout->addWidget(rotationGBox);
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
    applyRotationToImage(-rotationButtonStepSpinBox->value());
}

void OptionWidget::rotateRightButton()
{
    applyRotationToImage(rotationButtonStepSpinBox->value());
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
        rotationButtonsWidget->hide();
    } else {
        rotationWrappingDial->hide();
        rotationButtonsWidget->show();
    }
}
