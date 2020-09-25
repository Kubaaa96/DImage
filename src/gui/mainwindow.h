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
    void hideOptionWidget();
    void hideImageLayout();

private:
    Ui::MainWindow* ui;
    class ImageViewer* imageViewer;
    class QTreeWidget* treeOptionWidget;
    class QTreeWidgetItem* item;
    class ImageContainer* containerWidgetImages;
    class QVBoxLayout* verticalImagesLayout;
    class QLabel* testImage;
    class QPushButton* buttonImageViewHide;
    class QPushButton* buttonOptionsHide;

    void creatingContainerForImages();
    void creatingButtonToHideContainer();
    void creatingButtonToHideOptions();
    void settingUpMainLayout();
    void connectingCommands();
};

#endif // MAINWINDOW_H
