#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget* parent)
    : QGraphicsView(parent)
{
    empty = true;
    photo = new QGraphicsPixmapItem();
    scene = new QGraphicsScene(this);
    scene->addItem(photo);
    this->setScene(scene);
    zoom = 0;
}

ImageViewer::~ImageViewer()
{
}

void ImageViewer::setPhoto(QImage image)
{
    zoom = 0;
    QPixmap pixmapPhoto = QPixmap::fromImage(image);
    if (pixmapPhoto.isNull()) {
        empty = true;
        setDragMode(QGraphicsView::NoDrag);
        photo->setPixmap(QPixmap());
    } else {
        empty = false;
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        photo->setPixmap(pixmapPhoto);
    }
    //printf(empty ? "true" : "false");
    fitInView(photo);
}
