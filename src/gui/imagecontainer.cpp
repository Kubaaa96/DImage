#include "imagecontainer.h"

#include <QAction>
#include <QDebug>
#include <QMenu>
#include <QPoint>

ImageContainer::ImageContainer(QWidget* parent)
    : QListWidget(parent)
{
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(200, 200));
    this->setResizeMode(QListWidget::Adjust);
    this->setDragDropMode(DragDropMode::NoDragDrop);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(this, &QListWidget::customContextMenuRequested, this, &ImageContainer::ShowContextMenu);
}

ImageContainer::~ImageContainer()
{
}

void ImageContainer::addItemToContainer(const QIcon& icon, const QString& text)
{
}

void ImageContainer::action1()
{
    QListWidgetItem* clickedItem = this->itemAt(clickedPosition);
    if (clickedItem) {
        qInfo() << clickedItem->text();
    }
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
