#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget* parent)
    : QGraphicsView(parent)
{
    clearPhoto();
    scene = new QGraphicsScene(this);
    scene->addItem(photo);
    setScene(scene);
}

ImageViewer::~ImageViewer()
{
    delete photo;
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
    // TODO based on choosen option in Option Widget
    fitInView(photo);
}

void ImageViewer::wheelEvent(QWheelEvent* event)
{
    if (hasPhoto()) {
        float factor = 1;
        if (event->angleDelta().y() > 0) {
            factor = 1.25f;
            zoom += 1;
        } else {
            factor = 0.8f;
            zoom -= 1;
        }
        if (zoom > 0) {
            scale(factor, factor);
        } else if (zoom == 0) {
            fitInView(photo);
        } else {
            zoom = 0;
        }
    }
}

bool ImageViewer::hasPhoto()
{
    return !empty;
}

QImage ImageViewer::getPhoto()
{
    return photo->pixmap().toImage();
}

QGraphicsPixmapItem* ImageViewer::getPhotoAsGraphicsPixmapItem()
{
    return photo;
}

void ImageViewer::clearPhoto()
{
    empty = true;
    photo = new QGraphicsPixmapItem();
}
