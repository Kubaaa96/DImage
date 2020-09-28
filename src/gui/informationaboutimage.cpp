#include "informationaboutimage.h"
#include "ui_informationaboutimage.h"

#include <QFileInfo>

InformationAboutImage::InformationAboutImage(const QImage& image, const QString path, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::InformationAboutImage)
    , image(image)
    , path(path)
{
    ui->setupUi(this);
    ui->labelImage->setPixmap(QPixmap::fromImage(image));
    ui->labelName->setText("Name: " + QFileInfo(path).fileName());
    ui->labelOriginalSize->setText("Original size: " + QString::number(image.size().width()) + " x " + QString::number(image.size().height()));
    ui->labelPath->setText("Path: " + path);
}

InformationAboutImage::~InformationAboutImage()
{
    delete ui;
}
