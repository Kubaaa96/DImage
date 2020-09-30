#ifndef INFORMATIONABOUTIMAGE_H
#define INFORMATIONABOUTIMAGE_H

#include <QWidget>

namespace Ui {
class InformationAboutImage;
}

class InformationAboutImage : public QWidget {
    Q_OBJECT

public:
    explicit InformationAboutImage(QWidget* parent = nullptr);
    ~InformationAboutImage();
    void setupInformation(const QImage& imageToSetup, const QString pathToSetup);

private:
    Ui::InformationAboutImage* ui;
    const QSize sizeOfScalledImage{ 400, 400 };
};

#endif // INFORMATIONABOUTIMAGE_H
