#include "informationaboutimage.h"
#include "ui_informationaboutimage.h"

InformationAboutImage::InformationAboutImage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InformationAboutImage)
{
  ui->setupUi(this);
}

InformationAboutImage::~InformationAboutImage()
{
  delete ui;
}
