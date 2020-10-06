#ifndef OPENCVOPERATIONS_H
#define OPENCVOPERATIONS_H
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
class OpenCVOperations {

public:
    explicit OpenCVOperations(QImage imageToEdit = QImage());
    ~OpenCVOperations() = default;
    cv::Mat cannyEdgeDetection(double minThreshhold, double maxThreshhold);
    QImage cannyEdgeDetectionQt(double minThreshhold, double maxThreshhold);
    cv::Mat rotateImage();
    QImage rotateImageQt();
    void setOriginalPhoto(QImage image);

private:
    cv::Mat photoToEdit;
    QImage originalPhoto;
    QImage::Format originalPhotoFormat;
    QImage toImage(cv::Mat& cvImage, QImage::Format format);
    cv::Mat toMat(QImage& img, int format);
};

#endif // OPENCVOPERATIONS_H
