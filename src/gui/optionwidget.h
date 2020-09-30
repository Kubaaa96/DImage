#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QTabWidget>

namespace Ui {
class OptionWidget;
}

class OptionWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit OptionWidget(QWidget* parent = nullptr);
    ~OptionWidget();

private:
    Ui::OptionWidget* ui;

    QWidget* baseTab;
    QWidget* openCVTab;
    QWidget* computerVisionTab;

    void setupBaseTab();
    void setupOpenCVTab();
    void setupComputerVisionTab();
};

#endif // OPTIONWIDGET_H
