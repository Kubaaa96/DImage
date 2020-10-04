#include "openCVOperations.h"

OpenCVOperations::OpenCVOperations(QImage imageToEdit)
    : originalPhoto(toMat(imageToEdit, imageToEdit.format()))
{
}

cv::Mat OpenCVOperations::cannyEdgeDetection(double minThreshhold, double maxThreshhold)
{
    cv::Mat outputImage;
    cv::Canny(originalPhoto, outputImage, minThreshhold, maxThreshhold);
    return outputImage;
}

QImage OpenCVOperations::toImage(cv::Mat& cvImage, QImage::Format format)
{
    return QImage(cvImage.data, cvImage.cols, cvImage.rows, format);
}

cv::Mat OpenCVOperations::toMat(QImage& qImage, int format)
{
    return cv::Mat(qImage.height(), qImage.width(),
        format, qImage.bits(), qImage.bytesPerLine());
}
