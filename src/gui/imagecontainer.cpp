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
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(200, 200));
    this->setResizeMode(QListWidget::Adjust);
    this->setDragDropMode(DragDropMode::NoDragDrop);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    vectorOfImages = new QVector<QImage>;

    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(this, &QListWidget::customContextMenuRequested, this, &ImageContainer::ShowContextMenu);
    connect(this, &QListWidget::itemClicked, this, &ImageContainer::settingPhotoToMainImageViewer);
}

ImageContainer::~ImageContainer()
{
    delete vectorOfImages;
    delete informationWindow;
}

void ImageContainer::addItemToContainer(QImage& image, QString name)
{
    vectorOfImages->append(image);
    this->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(image)), name));
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
    if (this->count() > 0 && this != nullptr && QMessageBox::Yes == QMessageBox::warning(this, tr("Deleting %1").arg(this->itemAt(clickedPosition)->text()), "Are you sure you want to Delete this Image", QMessageBox::Yes | QMessageBox::No)) {

        int indexOfClickedItem = this->row(this->itemAt(clickedPosition));

        vectorOfImages->removeAt(indexOfClickedItem);
        QListWidgetItem* itemToDelete = this->takeItem(indexOfClickedItem);
        delete itemToDelete;
        if (indexOfClickedItem > 0) {
            instanceOfImageViewer->setPhoto(vectorOfImages->at(indexOfClickedItem - 1));
        } else {
            instanceOfImageViewer->setPhoto(QImage());
        }
    }
}

void ImageContainer::showImageInformation()
{
    informationWindow = new InformationAboutImage();
    informationWindow->show();
    informationWindow->setAttribute(Qt::WA_QuitOnClose, false);
    informationWindow->setWindowTitle(tr("Information about image: %1").arg(this->itemAt(clickedPosition)->text()));
}

void ImageContainer::settingPhotoToMainImageViewer()
{
    //qInfo() << vectorOfImages->isEmpty() ;
    //printf(vectorOfImages->isEmpty() ? "true" : "false");
    instanceOfImageViewer->setPhoto(vectorOfImages->at(this->selectionModel()->selectedIndexes().first().row()));
}

void ImageContainer::ShowContextMenu(const QPoint& pos)
{
    clickedPosition = pos;
    QMenu contextMenu("Context menu", this);
    QAction saveSelectedFile("Save As", this);
    QAction deleteImage("Delete", this);
    QAction informationAboutImage("Info", this);

    connect(&saveSelectedFile, &QAction::triggered, this, &ImageContainer::saveSelectedFile);
    connect(&deleteImage, &QAction::triggered, this, &ImageContainer::deleteImage);
    connect(&informationAboutImage, &QAction::triggered, this, &ImageContainer::showImageInformation);

    contextMenu.addAction(&saveSelectedFile);
    contextMenu.addAction(&deleteImage);
    contextMenu.addAction(&informationAboutImage);

    contextMenu.exec(mapToGlobal(pos));
}
