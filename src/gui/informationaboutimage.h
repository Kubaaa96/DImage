#ifndef INFORMATIONABOUTIMAGE_H
#define INFORMATIONABOUTIMAGE_H

#include <QWidget>

namespace Ui {
class InformationAboutImage;
}

class InformationAboutImage : public QWidget {
    Q_OBJECT

public:
    explicit InformationAboutImage(const QImage& image, const QString path, QWidget* parent = nullptr);
    ~InformationAboutImage();

private:
    Ui::InformationAboutImage* ui;
    QImage image;
    QString path;
};

#endif // INFORMATIONABOUTIMAGE_H
