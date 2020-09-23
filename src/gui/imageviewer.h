#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QWidget>

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QGraphicsView {
    Q_OBJECT

public:
    explicit ImageViewer(QGraphicsView* parent = nullptr);
    ~ImageViewer();

private:
};

#endif // IMAGEVIEWER_H
