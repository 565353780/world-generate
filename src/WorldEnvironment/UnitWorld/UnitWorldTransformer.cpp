#include "UnitWorldTransformer.h"

bool UnitWorldTransformer::reset()
{
    if(!resetImageSize())
    {
    }

    return true;
}

bool UnitWorldTransformer::resetImageSize()
{
    image_width_ = 0;
    image_height_ = 0;
    free_area_width_ = 0;

    resetTransform();

    return true;
}

bool UnitWorldTransformer::resetTransform()
{
    x_min_ = std::numeric_limits<float>::max();
    y_min_ = std::numeric_limits<float>::max();
    x_max_ = std::numeric_limits<float>::min();
    y_max_ = std::numeric_limits<float>::min();

    zoom_ = -1;
    offset_x_ = -1;
    offset_y_ = -1;

    return true;
}

bool UnitWorldTransformer::setImageSize(
    const size_t& image_width,
    const size_t& image_height,
    const size_t& free_area_width)
{
    if(image_width == 0 || image_height == 0)
    {
        std::cout << "UnitWorldTransformer::setImageSize :\n" <<
          "Input :\n" <<
          "\t image_size = [" << image_width << "," <<
          image_height << "]\n" <<
          "\t free_area_width = " << free_area_width << std::endl <<
          "image size not valid!\n";

        return false;
    }

    if(image_width <= 2 * free_area_width || image_height <= 2 * free_area_width)
    {
        std::cout << "UnitWorldTransformer::setImageSize :\n" <<
          "Input :\n" <<
          "\t image_size = [" << image_width << "," <<
          image_height << "]\n" <<
          "\t free_area_width = " << free_area_width << std::endl <<
          "free_area_width out of range!\n";

        return false;
    }

    image_width_ = image_width;
    image_height_ = image_height;
    free_area_width_ = free_area_width;

    return true;
}

bool UnitWorldTransformer::expandArea(
    const float& position_x,
    const float& position_y)
{
    x_min_ = std::fmin(x_min_, position_x);
    y_min_ = std::fmin(y_min_, position_y);
    x_max_ = std::fmax(x_max_, position_x);
    y_max_ = std::fmax(y_max_, position_y);

    return true;
}

bool UnitWorldTransformer::updateTransform()
{
    if(image_width_ == 0 || image_height_ == 0)
    {
        std::cout << "UnitWorldTransformer::updateTransform :\n" <<
          "image size not valid!\n";

        return false;
    }

    if(x_min_ > x_max_ || y_min_ > y_max_)
    {
        std::cout << "UnitWorldTransformer::updateTransform :\n" <<
          "no wall generated!\n";

        return false;
    }

    const float wall_x_diff = x_max_ - x_min_;
    const float wall_y_diff = y_max_ - y_min_;

    if(wall_x_diff == 0 && wall_y_diff == 0)
    {
        std::cout << "UnitWorldTransformer::updateTransform :\n" <<
          "wall area not valid!\n";

        return false;
    }

    zoom_ = std::numeric_limits<float>::max();

    if(wall_x_diff > 0)
    {
        zoom_ = std::fmin(zoom_, 1.0 * (image_width_ - 2.0 * free_area_width_) / wall_x_diff);
    }
    if(wall_y_diff > 0)
    {
        zoom_ = std::fmin(zoom_, 1.0 * (image_height_ - 2.0 * free_area_width_) / wall_y_diff);
    }

    const float wall_center_x = (x_min_ + x_max_) / 2.0;
    const float wall_center_y = (y_min_ + y_max_) / 2.0;

    const float zoomed_wall_center_x = wall_center_x * zoom_;
    const float zoomed_wall_center_y = wall_center_y * zoom_;

    offset_x_ = 0.5 * image_width_ - zoomed_wall_center_x;
    offset_y_ = 0.5 * image_height_ - zoomed_wall_center_y;

    std::cout << "wall size = " << x_min_ << "," << x_max_ << ";" <<
      y_min_ << "," << y_max_ << std::endl <<
      "zoom = " << zoom_ << std::endl <<
      "offset = " << offset_x_ << "," << offset_y_ << std::endl;

    return true;
}

bool UnitWorldTransformer::transPointToImage(
    const float& point_x_in_world,
    const float& point_y_in_world,
    size_t& point_x_in_image,
    size_t& point_y_in_image)
{
    point_x_in_image = size_t(point_x_in_world * zoom_ + offset_x_);
    point_y_in_image = size_t(point_y_in_world * zoom_ + offset_y_);

    return true;
}

bool UnitWorldTransformer::transPointToWorld(
    const size_t& point_x_in_image,
    const size_t& point_y_in_image,
    float& point_x_in_world,
    float& point_y_in_world)
{
    point_x_in_world = (1.0 * point_x_in_image - offset_x_) / zoom_;
    point_y_in_world = (1.0 * point_y_in_image - offset_y_) / zoom_;

    return true;
}

