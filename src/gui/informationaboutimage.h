#ifndef INFORMATIONABOUTIMAGE_H
#define INFORMATIONABOUTIMAGE_H

#include <QWidget>

namespace Ui {
  class InformationAboutImage;
}

class InformationAboutImage : public QWidget
{
  Q_OBJECT

public:
  explicit InformationAboutImage(QWidget *parent = nullptr);
  ~InformationAboutImage();

private:
  Ui::InformationAboutImage *ui;
};

#endif // INFORMATIONABOUTIMAGE_H
