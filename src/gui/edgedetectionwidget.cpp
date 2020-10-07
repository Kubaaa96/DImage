#include "edgedetectionwidget.h"
#include "ui_edgedetectionwidget.h"

#include <QHBoxLayout>
#include <QImage>

EdgeDetectionWidget::EdgeDetectionWidget(ImageViewer* imageViewer, QWidget* parent)
    : instanceOfImageViewer(imageViewer)
    , AbstractOperationWidget(parent)
    , ui(new Ui::EdgeDetectionWidget)
{
    ui->setupUi(this);

    setTitle("Canny Edge Algorithm");
    mainVBLayout = new QVBoxLayout(this);
    setupCheckBox();
    setupMinValue();
    setupMaxValue();
    connectGUIElements();
}

EdgeDetectionWidget::~EdgeDetectionWidget()
{
    delete ui;
}

void EdgeDetectionWidget::applyOperation()
{
    auto originalImage = instanceOfImageViewer->getPhoto();
    openCVOperations->setOriginalPhoto(originalImage);
    if (instanceOfImageViewer->hasPhoto() && controlCheckBox->checkState() == Qt::CheckState::Checked) {
        instanceOfImageViewer->setPhoto(
            openCVOperations->cannyEdgeDetectionQt(minThreshhold, maxThreshhold),
            Qt::AspectRatioMode::KeepAspectRatio);
    } else {
        qInfo() << "Canny Edge Unchecked";
        // TODO check Why not working
        instanceOfImageViewer->setPhoto(originalImage, Qt::AspectRatioMode::KeepAspectRatio);
    }
}

void EdgeDetectionWidget::setMinValue()
{
    minValueLabel->setText(QString::number(minSlider->value()));
    minThreshhold = static_cast<double>(minSlider->value());
}

void EdgeDetectionWidget::setMinValueFromLineEdit()
{
    int lowThreshold = minLineEdit->text().toInt();
    bool isMinValueInRange = minValueOfSlider < lowThreshold && lowThreshold < maxValueOfSlider;
    if (!minLineEdit->text().isEmpty() && isMinValueInRange) {
        minValueLabel->setText(minLineEdit->text());
        minThreshhold = lowThreshold;
        minSlider->setSliderPosition(lowThreshold);
        minThreshhold = lowThreshold;
    } else {
        qInfo() << "Min Value Line Edit Empty or out of allowed range";
    }
}

void EdgeDetectionWidget::setMaxValue()
{
    maxValueLabel->setText(QString::number(maxSlider->value()));
    maxThreshhold = static_cast<double>(maxSlider->value());
}

void EdgeDetectionWidget::setMaxValueFromLineEdit()
{
    int highThreshold = maxLineEdit->text().toInt();
    // Following Canny's recomendation highThreshold = LowerThreshold * 3
    bool isMaxValueInRange = minValueOfSlider * 3 < highThreshold && highThreshold < maxValueOfSlider * 3;
    if (!maxLineEdit->text().isEmpty() && isMaxValueInRange) {
        maxValueLabel->setText(maxLineEdit->text());
        maxThreshhold = highThreshold;
        maxSlider->setSliderPosition(highThreshold);
        maxThreshhold = highThreshold;
    } else {
        qInfo() << "Max Value Line Edit Empty or out of allowed range";
    }
}

void EdgeDetectionWidget::connectGUIElements()
{
    connect(controlCheckBox, &QCheckBox::stateChanged, this, &EdgeDetectionWidget::applyOperation);
    connect(minSlider, &QSlider::valueChanged, this, &EdgeDetectionWidget::setMinValue);
    connect(minLineEdit, &QLineEdit::editingFinished, this, &EdgeDetectionWidget::setMinValueFromLineEdit);
    connect(maxSlider, &QSlider::valueChanged, this, &EdgeDetectionWidget::setMaxValue);
    connect(maxLineEdit, &QLineEdit::editingFinished, this, &EdgeDetectionWidget::setMaxValueFromLineEdit);
}

void EdgeDetectionWidget::setupCheckBox()
{
    controlCheckBox = new QCheckBox("Canny Edge detector");
    mainVBLayout->addWidget(controlCheckBox);
}

void EdgeDetectionWidget::setupMinValue()
{
    auto HBLayout = new QHBoxLayout();

    minValueLabel = new QLabel("0");
    minValueLabel->setMinimumWidth(minWidthOfLabels);
    HBLayout->addWidget(minValueLabel);

    minSlider = new QSlider(Qt::Orientation::Horizontal);
    minThreshhold = minValueOfSlider;
    minSlider->setMinimum(minValueOfSlider);
    minSlider->setMaximum(maxValueOfSlider);
    minValueLabel->setText(QString::number(minSlider->value()));
    HBLayout->addWidget(minSlider);

    minLineEdit = new QLineEdit();
    minLineEdit->setMaximumWidth(maxWidthOfLineEdits);
    HBLayout->addWidget(minLineEdit);

    mainVBLayout->addLayout(HBLayout);
}

void EdgeDetectionWidget::setupMaxValue()
{
    auto HBLayout = new QHBoxLayout();

    maxValueLabel = new QLabel("100");
    maxValueLabel->setMinimumWidth(minWidthOfLabels);
    HBLayout->addWidget(maxValueLabel);

    maxSlider = new QSlider(Qt::Orientation::Horizontal);
    // Following Canny's recomendation highThreshold = LowerThreshold * 3
    maxThreshhold = minValueOfSlider * 3.0;
    maxSlider->setMinimum(minValueOfSlider * 3);
    maxSlider->setMaximum(maxValueOfSlider * 3);
    maxValueLabel->setText(QString::number(maxSlider->value()));
    HBLayout->addWidget(maxSlider);

    maxLineEdit = new QLineEdit();
    maxLineEdit->setMaximumWidth(maxWidthOfLineEdits);
    HBLayout->addWidget(maxLineEdit);
    mainVBLayout->addLayout(HBLayout);
}
