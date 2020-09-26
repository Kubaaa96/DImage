#include "imagecontainer.h"
#include "imageviewer.h"

#include <QAction>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QImageWriter>
#include <QMenu>
#include <QMessageBox>
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

void ImageContainer::saveSelectedFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("SaveFile"), "D:", tr("Image Files (*.png *.jpg *.bmp)"));
    QImageWriter writer(fileName);
    if (!writer.write(vectorOfImages->at(this->row(this->itemAt(clickedPosition))))) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            tr("Cannot write %1: %2")
                .arg(QDir::toNativeSeparators(fileName)),
            writer.errorString());
        return;
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
    QAction saveSelectedFile("Save As", this);
    connect(&action1, &QAction::triggered, this, &ImageContainer::action1);
    connect(&saveSelectedFile, &QAction::triggered, this, &ImageContainer::saveSelectedFile);
    contextMenu.addAction(&action1);
    contextMenu.addAction(&saveSelectedFile);
    contextMenu.exec(mapToGlobal(pos));
}
