#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H

#include <QWidget>

namespace Ui {
  class ImageContainer;
}

class ImageContainer : public QWidget
{
  Q_OBJECT

public:
  explicit ImageContainer(QWidget *parent = nullptr);
  ~ImageContainer();

private:
};

#endif // IMAGECONTAINER_H
