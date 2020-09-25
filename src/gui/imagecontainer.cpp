#include "imagecontainer.h"
#include "imageviewer.h"

#include <QAction>
#include <QDebug>
#include <QImage>
#include <QMenu>
#include <QPoint>
#include <QVector>

ImageContainer::ImageContainer(ImageViewer* imageViewer, QWidget* parent)
    : instanceOfImageViewer(imageViewer)
    , QListWidget(parent)
{
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(200, 200));
    this->setResizeMode(QListWidget::Adjust);
    this->setDragDropMode(DragDropMode::NoDragDrop);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    vectorOfImages = new QVector<QImage>;

    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(this, &QListWidget::customContextMenuRequested, this, &ImageContainer::ShowContextMenu);
    connect(this, &QListWidget::itemSelectionChanged, this, &ImageContainer::showCurrentlySelected);
}

ImageContainer::~ImageContainer()
{
}

void ImageContainer::addItemToContainer(QImage& image, QString name)
{
    vectorOfImages->append(image);
    this->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(image)), name));
}

void ImageContainer::action1()
{
    QListWidgetItem* clickedItem = this->itemAt(clickedPosition);
    if (clickedItem) {
        qInfo() << clickedItem->text();
    }
}

void ImageContainer::showCurrentlySelected()
{
    //qInfo() << vectorOfImages->isEmpty() ;
    //printf(vectorOfImages->isEmpty() ? "true" : "false");
    instanceOfImageViewer->setPhoto(vectorOfImages->at(this->selectionModel()->selectedIndexes().first().row()));
}

void ImageContainer::ShowContextMenu(const QPoint& pos)
{
    clickedPosition = pos;
    QMenu contextMenu("Context menu", this);
    QAction action1("Text1", this);
    connect(&action1, &QAction::triggered, this, &ImageContainer::action1);
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));
}
