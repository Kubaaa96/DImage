#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QGraphicsView {
    Q_OBJECT

public:
    explicit ImageViewer(QWidget* parent = nullptr);
    ~ImageViewer();
    void setPhoto(QImage image);

private:
    bool empty;
    QGraphicsPixmapItem* photo;
    QGraphicsScene* scene;
    float zoom;
};

#endif // IMAGEVIEWER_H
