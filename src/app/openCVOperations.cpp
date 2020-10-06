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
}

QImage OpenCVOperations::cannyEdgeDetectionQt(double minThreshhold, double maxThreshhold)
{
    return toImage(cannyEdgeDetection(minThreshhold, maxThreshhold), QImage::Format_Grayscale8);
}

// TODO refactor
cv::Mat OpenCVOperations::rotateImage(double angle)
{
    photoToEdit = toMat(originalPhoto, CV_8UC4);
    double offsetX, offsetY;
    double width = photoToEdit.size().width;
    double height = photoToEdit.size().height;
    cv::Point2d center = cv::Point2d(width / 2, height / 2);
    cv::Rect bounds = cv::RotatedRect(center, photoToEdit.size(), angle).boundingRect();
    cv::Mat resizedImage = cv::Mat::zeros(bounds.size(), photoToEdit.type());
    offsetX = (bounds.width - width) / 2;
    offsetY = (bounds.height - height) / 2;
    cv::Rect roi = cv::Rect(offsetX, offsetY, width, height);
    photoToEdit.copyTo(resizedImage(roi));
    center += cv::Point2d(offsetX, offsetY);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1);
    cv::warpAffine(resizedImage, resizedImage, rotationMatrix, resizedImage.size());
    cv::cvtColor(resizedImage, resizedImage, cv::COLOR_RGBA2RGB);
    qInfo() << QString::fromStdString(getImageType(resizedImage.type()));
    return resizedImage;
}

QImage OpenCVOperations::rotateImageQt(double angle)
{
    return toImage(rotateImage(angle), QImage::Format_RGB888).rgbSwapped();
}

void OpenCVOperations::setOriginalPhoto(QImage image)
{
    originalPhoto = image;
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

std::string OpenCVOperations::getImageType(int number)
{
    // find type
    int imgTypeInt = number % 8;
    std::string imgTypeString;

    switch (imgTypeInt) {
    case 0:
        imgTypeString = "8U";
        break;
    case 1:
        imgTypeString = "8S";
        break;
    case 2:
        imgTypeString = "16U";
        break;
    case 3:
        imgTypeString = "16S";
        break;
    case 4:
        imgTypeString = "32S";
        break;
    case 5:
        imgTypeString = "32F";
        break;
    case 6:
        imgTypeString = "64F";
        break;
    default:
        break;
    }

    // find channel
    int channel = (number / 8) + 1;

    std::stringstream type;
    type << "CV_" << imgTypeString << "C" << channel;

    return type.str();
}
