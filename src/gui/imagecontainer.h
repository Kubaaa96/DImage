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
    void settingPhotoToMainImageViewer();
    void saveSelectedFile();
    void deleteImage();
    void showImageInformation();

private:
    QPoint clickedPosition;
    QVector<QImage>* vectorOfImages;
    ImageViewer* instanceOfImageViewer;
    class InformationAboutImage* informationWindow;
};

#endif // IMAGECONTAINER_H
