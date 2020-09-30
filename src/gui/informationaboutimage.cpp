#include "informationaboutimage.h"
#include "ui_informationaboutimage.h"

#include <QFileInfo>

InformationAboutImage::InformationAboutImage(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::InformationAboutImage)

{
    ui->setupUi(this);
}

InformationAboutImage::~InformationAboutImage()
{
    delete ui;
}

void InformationAboutImage::setupInformation(const QImage& imageToSetup, const QString pathToSetup)
{
    QImage tempImage = imageToSetup.scaled(sizeOfScalledImage, Qt::AspectRatioMode::KeepAspectRatio);
    ui->labelImage->setPixmap(QPixmap::fromImage(tempImage));
    ui->labelName->setText("Name: " + QFileInfo(pathToSetup).fileName());
    ui->labelOriginalSize->setText("Original size: " + QString::number(imageToSetup.size().width()) + " x " + QString::number(imageToSetup.size().height()));
    ui->labelPath->setText("Path: " + pathToSetup);
}
