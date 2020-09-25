#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H

#include <QListWidget>

namespace Ui {
class ImageContainer;
}

class ImageContainer : public QListWidget {
    Q_OBJECT

public:
    explicit ImageContainer(QWidget* parent = nullptr);
    ~ImageContainer();
    void addItemToContainer(const QIcon& icon, const QString& text);

public slots:
    void ShowContextMenu(const QPoint& pos);
    void action1();

private:
    QPoint clickedPosition;
};

#endif // IMAGECONTAINER_H
