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
    void addItemToContainer(QImage& image, QString filePath);

public slots:
    void ShowContextMenu(const QPoint& pos);
    void settingPhotoToMainImageViewer();
    void saveSelectedFile();
    void deleteImage();
    void showImageInformation();
    void clickOnItem();

private:
    QPoint clickedPosition;
    QVector<QImage>* vectorOfImages;
    QVector<QString>* vectorOfImagePaths;
    class ImageViewer* instanceOfImageViewer;
    class InformationAboutImage* informationWindow;

    int indexOfClickedItem { 0 };
    const QSize iconSize { 200, 200 };
};

#endif // IMAGECONTAINER_H
