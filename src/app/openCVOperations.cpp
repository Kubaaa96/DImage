#include "openCVOperations.h"
OpenCVOperations::OpenCVOperations(QImage imageToEdit)
    : originalPhoto(imageToEdit)
    , originalPhotoFormat(imageToEdit.format())
{
}

cv::Mat OpenCVOperations::cannyEdgeDetection(double minThreshhold, double maxThreshhold)
{
    cv::cvtColor(toMat(originalPhoto, CV_8UC4), photoToEdit, cv::COLOR_RGBA2GRAY);
    auto edgedImage = cv::Mat(photoToEdit);
    cv::Canny(photoToEdit, edgedImage, minThreshhold, maxThreshhold);
    return edgedImage;
    //qInfo() << originalPhotoFormat;
}

QImage OpenCVOperations::cannyEdgeDetectionQ(double minThreshhold, double maxThreshhold)
{
    return toImage(cannyEdgeDetection(minThreshhold, maxThreshhold), QImage::Format_Grayscale8);
}

QImage OpenCVOperations::getOriginalPhoto()
{
    return originalPhoto;
}

QImage OpenCVOperations::toImage(cv::Mat& cvImage, QImage::Format format)
{
    return QImage(cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, format);
}

cv::Mat OpenCVOperations::toMat(QImage& qImage, int format)
{
    return cv::Mat(qImage.height(), qImage.width(),
        format, qImage.bits(), qImage.bytesPerLine());
}
