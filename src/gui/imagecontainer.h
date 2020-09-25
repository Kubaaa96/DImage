#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H

#include "imageviewer.h"
#include <QListWidget>

namespace Ui {
class ImageContainer;
}

class ImageContainer : public QListWidget {
    Q_OBJECT

public:
    explicit ImageContainer(ImageViewer* imageViewer, QWidget* parent = nullptr);
    //ImageContainer(ImageViewer* imageViewer, QWidget* parent);
    ~ImageContainer();
    // Should parameter be Const?
    void addItemToContainer(QImage& image, QString name);

public slots:
    void ShowContextMenu(const QPoint& pos);
    void action1();
    void showCurrentlySelected();

private:
    QPoint clickedPosition;
    QVector<QImage>* vectorOfImages;
    ImageViewer* instanceOfImageViewer;
};

#endif // IMAGECONTAINER_H
