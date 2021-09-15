#include "EasyBoundary.h"
#include <opencv2/core/types.hpp>

bool EasyBoundary::reset()
{
    boundary.reset();

    return true;
}

bool EasyBoundary::addBoundaryPoint(
    const EasyPoint2D &boundary_point)
{
    boundary.addPoint(boundary_point);

    boundary.setAntiClockWise();

    return true;
}

bool EasyBoundary::addBoundaryPoint(
    const float &x,
    const float &y)
{
    EasyPoint2D boundary_point;
    boundary_point.setPosition(x, y);
    
    return addBoundaryPoint(boundary_point);
}

bool EasyBoundary::setBoundaryPointVec(
    const std::vector<EasyPoint2D> &boundary_point_vec)
{
    boundary.point_list.clear();

    if(boundary_point_vec.size() == 0)
    {
        std::cout << "EasyBoundary::setBoundary : " <<
          "boundary_point_vec is empty!" << std::endl;

        return false;
    }

    for(const EasyPoint2D &boundary_point : boundary_point_vec)
    {
        addBoundaryPoint(boundary_point);
    }

    return true;
}

bool EasyBoundary::showBoundary()
{
    const size_t x_free = 20;
    const size_t y_free = 20;

    const float &x_diff = boundary.rect.x_diff;
    const float &y_diff = boundary.rect.y_diff;

    size_t image_width = size_t(x_diff) + 2 * x_free;
    size_t image_height = size_t(y_diff) + 2 * y_free;

    cv::Mat boundary_image = cv::Mat(image_height, image_width, CV_8UC3);

    if(boundary.point_list.size() < 2)
    {
        std::cout << "EasyBoundary::showBoundary : " <<
          "current boundary is empty!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < boundary.point_list.size(); ++i)
    {
        const EasyPoint2D &current_point = boundary.point_list[i];
        const EasyPoint2D &next_point = boundary.point_list[(i + 1) % boundary.point_list.size()];

        cv::Point current_cv_point = cv::Point(
            size_t(current_point.x - boundary.rect.x_min) + x_free,
            size_t(current_point.y - boundary.rect.y_min) + y_free);
        cv::Point next_cv_point = cv::Point(
            size_t(next_point.x - boundary.rect.x_min) + x_free,
            size_t(next_point.y - boundary.rect.y_min) + y_free);

        cv::line(boundary_image, current_cv_point, next_cv_point, cv::Scalar(0, 0, 255), 3);
    }

    cv::imshow("boundary_image", boundary_image);
    cv::waitKey(0);

    return true;
}
