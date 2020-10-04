#ifndef OPENCVOPERATIONS_H
#define OPENCVOPERATIONS_H
#include <QImage>
#include <QPixmap>
#include <opencv2/imgproc.hpp>

class OpenCVOperations {

public:
    explicit OpenCVOperations(QImage imageToEdit);
    ~OpenCVOperations() = default;
    cv::Mat cannyEdgeDetection(double minThreshhold, double maxThreshhold);

    QImage toImage(cv::Mat& cvImage, QImage::Format format);

private:
    cv::Mat originalPhoto;

    cv::Mat toMat(QImage& img, int format);
};

#endif // OPENCVOPERATIONS_H
