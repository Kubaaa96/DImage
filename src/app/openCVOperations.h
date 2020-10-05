#ifndef OPENCVOPERATIONS_H
#define OPENCVOPERATIONS_H
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
class OpenCVOperations {

public:
    explicit OpenCVOperations(QImage imageToEdit);
    ~OpenCVOperations() = default;
    cv::Mat cannyEdgeDetection(double minThreshhold, double maxThreshhold);
    QImage cannyEdgeDetectionQ(double minThreshhold, double maxThreshhold);

private:
    cv::Mat photoToEdit;
    QImage originalPhoto;
    QImage::Format originalPhotoFormat;
    QImage toImage(cv::Mat& cvImage, QImage::Format format);
    cv::Mat toMat(QImage& img, int format);
};

#endif // OPENCVOPERATIONS_H
