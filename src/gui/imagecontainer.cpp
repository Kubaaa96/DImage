#include "imagecontainer.h"
#include "imageviewer.h"
#include "informationaboutimage.h"

#include <QAction>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QImageWriter>
#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QPoint>
#include <QVector>

ImageContainer::ImageContainer(ImageViewer* imageViewer, QWidget* parent)
    : instanceOfImageViewer(imageViewer)
    , QListWidget(parent)
{
    setViewMode(QListWidget::IconMode);
    setIconSize(iconSize);
    setResizeMode(QListWidget::Adjust);
    setDragDropMode(DragDropMode::NoDragDrop);
    setContextMenuPolicy(Qt::CustomContextMenu);

    vectorOfImages = new QVector<QImage>;
    vectorOfImagePaths = new QVector<QString>;
    informationWindow = new InformationAboutImage();

    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(this, &QListWidget::customContextMenuRequested, this, &ImageContainer::ShowContextMenu);
    connect(this, &QListWidget::itemClicked, this, &ImageContainer::settingPhotoToMainImageViewer);
}

ImageContainer::~ImageContainer()
{
    delete vectorOfImages;
    delete vectorOfImagePaths;
    delete informationWindow;
}

void ImageContainer::addItemToContainer(QImage& image, QString filePath)
{
    vectorOfImages->append(image);
    vectorOfImagePaths->append(filePath);
    addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(image)), QFileInfo(filePath).fileName()));
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

void ImageContainer::deleteImage()
{
    if (count() > 0 && itemAt(clickedPosition) && QMessageBox::Yes == QMessageBox::warning(this, tr("Deleting %1").arg(this->itemAt(clickedPosition)->text()), "Are you sure you want to Delete this Image", QMessageBox::Yes | QMessageBox::No)) {

        int indexOfClickedItem = this->row(this->itemAt(clickedPosition));

        vectorOfImages->removeAt(indexOfClickedItem);
        QListWidgetItem* itemToDelete = this->takeItem(indexOfClickedItem);
        delete itemToDelete;
        if (indexOfClickedItem > 0) {
            instanceOfImageViewer->setPhoto(vectorOfImages->at(indexOfClickedItem - 1), Qt::AspectRatioMode::KeepAspectRatio);
        } else {
            instanceOfImageViewer->setPhoto(QImage(), Qt::AspectRatioMode::KeepAspectRatio);
        }
    }
}

void ImageContainer::showImageInformation()
{
    indexOfClickedItem = row(this->itemAt(clickedPosition));
    informationWindow->setupInformation(vectorOfImages->at(indexOfClickedItem), vectorOfImagePaths->at(indexOfClickedItem));
    informationWindow->show();
    informationWindow->setAttribute(Qt::WA_QuitOnClose, false);
    informationWindow->setWindowTitle(tr("Information about image: %1").arg(this->itemAt(clickedPosition)->text()));
}

void ImageContainer::clickOnItem()
{
    QMessageBox::warning(this, "CLICK ON ITEM", "I SAID CLICK ON THE ITEM FOR MORE OPTION", QMessageBox::Yes, QMessageBox::Yes);
}

void ImageContainer::settingPhotoToMainImageViewer()
{
    auto currentPhoto = vectorOfImages->at(selectionModel()->selectedIndexes().first().row());
    instanceOfImageViewer->setPhoto(currentPhoto, Qt::AspectRatioMode::KeepAspectRatio);
}

void ImageContainer::ShowContextMenu(const QPoint& pos)
{
    clickedPosition = pos;
    QMenu contextMenu("Context menu", this);
    QAction saveSelectedFile("Save As", this);
    QAction deleteImage("Delete", this);
    QAction informationAboutImage("Info", this);
    QAction itemNotClicked("Click on Item to see more options", this);

    connect(&saveSelectedFile, &QAction::triggered, this, &ImageContainer::saveSelectedFile);
    connect(&deleteImage, &QAction::triggered, this, &ImageContainer::deleteImage);
    connect(&informationAboutImage, &QAction::triggered, this, &ImageContainer::showImageInformation);
    connect(&itemNotClicked, &QAction::triggered, this, &ImageContainer::clickOnItem);

    if (itemAt(clickedPosition)) {
        contextMenu.addAction(&saveSelectedFile);
        contextMenu.addAction(&deleteImage);
        contextMenu.addAction(&informationAboutImage);
    } else {
        contextMenu.addAction(&itemNotClicked);
    }

    contextMenu.exec(mapToGlobal(pos));
}
