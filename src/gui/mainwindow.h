#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

public slots:
    void openFile();
    void saveFile();
    void hideOptionWidget();
    void hideImageLayout();
    void about();

private:
    Ui::MainWindow* ui;
    class ImageViewer* imageViewer;
    class OptionWidget* optionWidget;
    class AboutWidget* aboutWidget;
    class ImageContainer* containerWidgetImages;
    class QPushButton* buttonImageViewHide;
    class QPushButton* buttonOptionsHide;
    class QImage loadedImage;

    void creatingContainerForImages();
    void creatingOptionsWidget();
    void creatingButtonToHideContainer();
    void creatingButtonToHideOptions();
    void settingUpMainLayout();
    void connectingCommands();

    void addItemToContainerAndSetPhotoToViewer(QImage& image, QString path, bool isFirstImageSetup);

    const int maximumWidthOfHidingButtons { 30 };
    const int maximumWidthOfSidesWidgets { 250 };
};

#endif // MAINWINDOW_H
