#include "SpaceController.h"
#include <limits>

bool SpaceController::createBoundary(
    const std::string &boundary_name)
{
    EasyBoundary new_boundary;
    new_boundary.name = boundary_name;

    boundary_vec_.emplace_back(new_boundary);

    return true;
}

bool SpaceController::createRoom(
    const std::string &room_name)
{
    EasyRoom new_room;
    new_room.name = room_name;

    room_vec_.emplace_back(new_room);

    return true;
}

bool SpaceController::setOuterBoundary(
    const size_t &boundary_idx)
{
    if(boundary_idx >= boundary_vec_.size())
    {
        std::cout << "SpaceController::setOuterBoundary : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    if(!boundary_vec_[boundary_idx].setOuterBoundary())
    {
        std::cout << "SpaceController::setOuterBoundary : " <<
          "setOuterBoundary failed for boundary-" << boundary_idx << "!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::setBoundaryPointVec(
    const size_t &boundary_idx,
    const std::vector<EasyPoint2D> &boundary_point_vec)
{
    if(boundary_idx >= boundary_vec_.size())
    {
        std::cout << "SpaceController::setBoundaryPointVec : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    EasyBoundary &boundary = boundary_vec_[boundary_idx];

    boundary.reset();

    if(!boundary.setBoundaryPointVec(boundary_point_vec))
    {
        std::cout << "SpaceController::createBoundary : " <<
          "set Boundary Point Vec failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::addBoundaryPoint(
    const size_t &boundary_idx,
    const EasyPoint2D &boundary_point)
{
    if(boundary_idx >= boundary_vec_.size())
    {
        std::cout << "SpaceController::setBoundaryPointVec : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    EasyBoundary &boundary = boundary_vec_[boundary_idx];

    if(!boundary.addBoundaryPoint(boundary_point))
    {
        std::cout << "SpaceController::addBoundaryPoint : " <<
          "add Boundary Point failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::addBoundaryPoint(
    const size_t &boundary_idx,
    const float &x,
    const float &y)
{
    if(boundary_idx >= boundary_vec_.size())
    {
        std::cout << "SpaceController::setBoundaryPointVec : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    EasyBoundary &boundary = boundary_vec_[boundary_idx];

    if(!boundary.addBoundaryPoint(x, y))
    {
        std::cout << "SpaceController::addBoundaryPoint : " <<
          "add Boundary Point failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::setRoomBoundaryPointParam(
    const size_t &room_idx,
    const size_t &boundary_idx,
    const size_t &boundary_line_idx,
    const float &boundary_line_param)
{
    if(room_idx >= room_vec_.size())
    {
        std::cout << "SpaceController::setRoomOnBoundaryParam : " <<
          "room idx out of range!" << std::endl;

        return false;
    }

    if(boundary_idx >= boundary_vec_.size())
    {
        std::cout << "SpaceController::setRoomOnBoundaryParam : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    const EasyBoundary &boundary = boundary_vec_[boundary_idx];

    if(boundary_line_idx >= boundary.boundary.point_list.size())
    {
        std::cout << "SpaceController::setRoomOnBoundaryParam : " <<
          "boundary line idx out of range!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::setRoomSize(
    const size_t &room_idx,
    const float &width,
    const float &height)
{
    if(room_idx >= room_vec_.size())
    {
        std::cout << "SpaceController::setRoomSize : " <<
          "room idx out of range!" << std::endl;

        return false;
    }

    if(!room_vec_[room_idx].setTargetSize(width, height))
    {
        std::cout << "SpaceController::setRoomSize : " <<
          "setTargetSize failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::setRoomNeighboor(
    const size_t &room_idx_1,
    const size_t &room_idx_2)
{
    if(room_idx_1 >= room_vec_.size())
    {
        std::cout << "SpaceController::setRoomNeighboor : " <<
          "room idx 1 out of range!" << std::endl;

        return false;
    }

    if(room_idx_2 >= room_vec_.size())
    {
        std::cout << "SpaceController::setRoomNeighboor : " <<
          "room idx 2 out of range!" << std::endl;

        return false;
    }

    EasyRoom &room_1 = room_vec_[room_idx_1];
    EasyRoom &room_2 = room_vec_[room_idx_2];

    room_1.addNeighboorRoomIdx(room_idx_2);
    room_2.addNeighboorRoomIdx(room_idx_1);

    return true;
}

bool SpaceController::generateSpace()
{
    if(!getSortedRoomLineVec())
    {
        std::cout << "SpaceController::generateSpace : " <<
          "getSortedRoomLineVec failed!" << std::endl;

        return false;
    }

    if(!updateRoomLineVecSize())
    {
        std::cout << "SpaceController::generateSpace : " <<
          "updateRoomLineVecSize failed!" << std::endl;

        return false;
    }

    room_line_boundary_point_vec_.resize(room_line_vec_.size(), EasyBoundaryPoint());
    room_line_boundary_line_vec_.resize(room_line_vec_.size(), EasyBoundaryLine());

    return true;
}

bool SpaceController::showBoundary()
{
    const size_t x_free = 20;
    const size_t y_free = 20;

    float x_min = std::numeric_limits<float>::max();
    float x_max = std::numeric_limits<float>::min();
    float y_min = std::numeric_limits<float>::max();
    float y_max = std::numeric_limits<float>::min();

    for(const EasyBoundary &boundary : boundary_vec_)
    {
        x_min = std::fmin(x_min, boundary.boundary.rect.x_min);
        x_max = std::fmax(x_max, boundary.boundary.rect.x_max);
        y_min = std::fmin(y_min, boundary.boundary.rect.y_min);
        y_max = std::fmax(y_max, boundary.boundary.rect.y_max);
    }

    const float &x_diff = x_max - x_min;
    const float &y_diff = y_max - y_min;

    size_t image_width = size_t(x_diff) + 2 * x_free;
    size_t image_height = size_t(y_diff) + 2 * y_free;

    cv::Mat boundary_image = cv::Mat(image_height, image_width, CV_8UC3);

    for(const EasyBoundary &boundary : boundary_vec_)
    {
        if(boundary.boundary.point_list.size() == 0)
        {
            continue;
        }

        for(size_t i = 0; i < boundary.boundary.point_list.size(); ++i)
        {
            const EasyPolygon2D &boundary_polygon = boundary.boundary;
            const EasyPoint2D &current_point = boundary_polygon.point_list[i];
            const EasyPoint2D &next_point = boundary_polygon.point_list[(i + 1) % boundary_polygon.point_list.size()];

            cv::Point current_cv_point = cv::Point(
                size_t(current_point.x - boundary_polygon.rect.x_min) + x_free,
                size_t(current_point.y - boundary_polygon.rect.y_min) + y_free);
            cv::Point next_cv_point = cv::Point(
                size_t(next_point.x - boundary_polygon.rect.x_min) + x_free,
                size_t(next_point.y - boundary_polygon.rect.y_min) + y_free);

            cv::line(boundary_image, current_cv_point, next_cv_point, cv::Scalar(0, 0, 255), 3);
        }
    }

    cv::imshow("boundary_image", boundary_image);
    cv::waitKey(0);

    return true;
}

bool SpaceController::updateRoomLineBoundaryPointPosition()
{
    if(room_line_boundary_point_vec_.size() == 0)
    {
        std::cout << "SpaceController::updateRoomLineBoundaryPointPosition : " <<
          "room line boundary point not found!" << std::endl;

        return false;
    }

    for(EasyBoundaryPoint &room_line_boundary_point : room_line_boundary_point_vec_)
    {
        if(!room_line_boundary_point.updatePosition(boundary_vec_))
        {
            std::cout << "SpaceController::updateRoomLineBoundaryPointPosition : " <<
              "updatePosition failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool SpaceController::outputRoomLine(
    const EasyRoomLine &room_line)
{
    std::cout << "RoomLine : ";

    for(const size_t room_idx : room_line.sorted_room_idx_line)
    {
        std::cout << room_idx << "(" << room_vec_[room_idx].name << ")" << " - ";
    }

    if(room_line.is_circle)
    {
        std::cout << "circle" << std::endl;
    }
    else
    {
        std::cout << "line" << std::endl;
    }

    return true;
}

bool SpaceController::outputRoomLineVec()
{
    for(const EasyRoomLine &room_line : room_line_vec_)
    {
        if(!outputRoomLine(room_line))
        {
            std::cout << "SpaceController::outputRoomLineVec : " <<
              "outputRoomLine failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool SpaceController::getRoomLine(
    const size_t &start_room_idx,
    const size_t &current_room_idx,
    EasyRoomLine &room_line)
{
    if(current_room_idx == start_room_idx)
    {
        room_line.is_circle = true;

        return true;
    }

    const size_t last_room_idx = room_line.sorted_room_idx_line.back();

    room_line.sorted_room_idx_line.emplace_back(current_room_idx);

    const EasyRoom &current_room = room_vec_[current_room_idx];

    if(current_room.neighboor_room_idx_vec.size() > 2)
    {
        std::cout << "SpaceController::getRoomLine : " <<
          "room-" << current_room_idx << " has more than 2 neighboor room!" << std::endl;
        
        return false;
    }

    if(current_room.neighboor_room_idx_vec.size() == 1)
    {
        return true;
    }

    if(current_room.neighboor_room_idx_vec[0] == last_room_idx)
    {
        const size_t &next_room_idx = current_room.neighboor_room_idx_vec[1];

        return getRoomLine(start_room_idx, next_room_idx, room_line);
    }

    const size_t &next_room_idx = current_room.neighboor_room_idx_vec[0];

    return getRoomLine(start_room_idx, next_room_idx, room_line);
}

bool SpaceController::getSortedRoomLine(
    const size_t &room_idx,
    EasyRoomLine &room_line)
{
    room_line.reset();

    if(room_idx >= room_vec_.size())
    {
        std::cout << "SpaceController::getSortedRoomLine : " <<
          "room idx out of range!" << std::endl;

        return false;
    }

    const EasyRoom &start_room = room_vec_[room_idx];

    if(start_room.neighboor_room_idx_vec.size() == 0)
    {
        room_line.sorted_room_idx_line.emplace_back(room_idx);

        return true;
    }

    if(start_room.neighboor_room_idx_vec.size() > 2)
    {
        std::cout << "SpaceController::getSortedRoomLine : " <<
          "room-" << room_idx << " has more than 2 neighboor room!" << std::endl;
        
        return false;
    }

    if(start_room.neighboor_room_idx_vec.size() == 1)
    {
        room_line.sorted_room_idx_line.emplace_back(room_idx);

        const size_t &next_room_idx = start_room.neighboor_room_idx_vec[0];

        if(!getRoomLine(room_idx, next_room_idx, room_line))
        {
            std::cout << "SpaceController::getSortedRoomLine : " <<
              "getRoomIdxLine failed!" << std::endl;

            return false;
        }

        return true;
    }

    EasyRoomLine room_line_1;

    room_line_1.sorted_room_idx_line.emplace_back(room_idx);

    const size_t &next_room_idx_1 = start_room.neighboor_room_idx_vec[0];

    if(!getRoomLine(room_idx, next_room_idx_1, room_line_1))
    {
        std::cout << "SpaceController::getSortedRoomLine : " <<
          "getRoomIdxLine 1 failed!" << std::endl;

        return false;
    }

    if(room_line_1.is_circle)
    {
        room_line = room_line_1;

        return true;
    }

    EasyRoomLine room_line_2;

    room_line_2.sorted_room_idx_line.emplace_back(room_idx);

    const size_t &next_room_idx_2 = start_room.neighboor_room_idx_vec[1];

    if(!getRoomLine(room_idx, next_room_idx_2, room_line_2))
    {
        std::cout << "SpaceController::getSortedRoomLine : " <<
          "getRoomIdxLine 2 failed!" << std::endl;

        return false;
    }

    if(room_line_1.sorted_room_idx_line.size() == 1)
    {
        room_line.sorted_room_idx_line.emplace_back(room_line_1.sorted_room_idx_line[0]);
    }
    else
    {
        for(size_t i = room_line_1.sorted_room_idx_line.size(); i > 0; --i)
        {
            room_line.sorted_room_idx_line.emplace_back(room_line_1.sorted_room_idx_line[i - 1]);
        }
    }

    if(room_line_2.sorted_room_idx_line.size() == 1)
    {
        return true;
    }

    for(size_t i = 1; i < room_line_2.sorted_room_idx_line.size(); ++i)
    {
        room_line.sorted_room_idx_line.emplace_back(room_line_2.sorted_room_idx_line[i]);
    }

    return true;
}

bool SpaceController::setRoomLineBoundaryPointParam(
    const size_t &room_line_idx,
    const size_t &boundary_idx,
    const size_t &boundary_line_idx,
    const float &boundary_line_param)
{
    if(room_line_idx >= room_line_vec_.size())
    {
        std::cout << "SpaceController::setRoomLineBoundaryPointParam : " <<
          "room line idx out of range!" << std::endl;

        return false;
    }

    if(boundary_idx >= boundary_vec_.size())
    {
        std::cout << "SpaceController::setRoomLineBoundaryPointParam : " <<
          "boundary idx out of range!" << std::endl;

        return false;
    }

    EasyBoundary &boundary = boundary_vec_[boundary_idx];

    if(boundary_line_idx >= boundary.boundary.point_list.size())
    {
        std::cout << "SpaceController::setRoomLineBoundaryPointParam : " <<
          "boundary line idx out of range!" << std::endl;

        return false;
    }

    if(boundary.haveThisRoomLineOnBoundary(room_line_idx))
    {
        std::cout << "SpaceController::setRoomLineBoundaryPointParam : " <<
          "boundary-" << boundary_idx << " already have room-line-" << room_line_idx << "!" << std::endl;

        return true;
    }

    boundary.exist_room_line_idx_vec.emplace_back(room_line_idx);

    if(!room_line_boundary_point_vec_[room_line_idx].setPositionParam(
          boundary_idx,
          boundary_line_idx,
          boundary_line_param))
    {
        std::cout << "SpaceController::addRoomLineOnBoundary : " <<
          "setPositionParam failed for room-line-" << room_line_idx << "!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::getSortedRoomLineVec()
{
    room_line_vec_.clear();

    if(room_vec_.size() == 0)
    {
        std::cout << "SpaceController::getRoomSortedIdxVec : " <<
          "room vec is empty!" << std::endl;

        return false;
    }

    size_t room_used_num = 0;
    std::vector<bool> room_used_vec;
    room_used_vec.resize(room_vec_.size(), false);

    while(room_used_num < room_vec_.size())
    {
        for(size_t i = 0; i < room_vec_.size(); ++i)
        {
            if(room_used_vec[i])
            {
                continue;
            }

            EasyRoomLine room_line;

            if(!getSortedRoomLine(i, room_line))
            {
                std::cout << "SpaceController::getSortedRoomLineVec : " <<
                  "getSortedRoomLine failed!" << std::endl;

                return false;
            }

            room_line_vec_.emplace_back(room_line);
            room_used_num += room_line.sorted_room_idx_line.size();

            for(const size_t &used_room_idx : room_line.sorted_room_idx_line)
            {
                room_used_vec[used_room_idx] = true;
            }

            break;
        }
    }

    return true;
}

bool SpaceController::updateRoomLineSize(
    EasyRoomLine &room_line)
{
    room_line.target_area = -1;
    room_line.target_width = -1;
    room_line.target_height = -1;

    if(room_line.sorted_room_idx_line.size() == 0)
    {
        std::cout << "SpaceController::updateRoomLineSize : " <<
          "room line is empty!" << std::endl;

        return false;
    }

    for(const size_t &room_idx : room_line.sorted_room_idx_line)
    {
        room_line.target_area += room_vec_[room_idx].target_area;
        room_line.target_width += room_vec_[room_idx].target_width;
    }

    return true;
}

bool SpaceController::updateRoomLineVecSize()
{
    for(EasyRoomLine &room_line : room_line_vec_)
    {
        if(!updateRoomLineSize(room_line))
        {
            std::cout << "SpaceController::updateRoomLineVecSize : " <<
              "updateRoomLineSize failed!" << std::endl;

            return false;
        }
    }

    return true;
}

