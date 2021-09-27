#include "SpaceController.h"
#include "highgui.hpp"
#include <limits>
#include <string>

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

    if(room_line_vec_.size() == 0)
    {
        std::cout << "SpaceController::setRoomOnBoundaryParam : " <<
          "room line is empty!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < room_line_vec_.size(); ++i)
    {
        EasyRoomLine &room_line = room_line_vec_[i];

        if(!room_line.haveThisRoom(room_idx))
        {
            continue;
        }

        float room_line_boundary_point_param;

        if(!getRoomLineBoundaryPointParam(
              room_line,
              boundary,
              room_idx,
              boundary_line_idx,
              boundary_line_param,
              room_line_boundary_point_param))
        {
            std::cout << "SpaceController::setRoomOnBoundaryParam : " <<
              "getRoomLineBoundaryPointParam failed for room-" << room_idx << "!" << std::endl;

            return false;
        }

        if(!setRoomLineBoundaryPointParam(
              i,
              boundary_idx,
              boundary_line_idx,
              room_line_boundary_point_param))
        {
            std::cout << "SpaceController::setRoomOnBoundaryParam : " <<
              "setRoomLineBoundaryPointParam failed for room-" << room_idx << "!" << std::endl;

            return false;
        }

        return true;
    }

    return true;
}

bool SpaceController::updateBoundary()
{
    if(boundary_vec_.size() == 0)
    {
        std::cout << "SpaceController::updateBoundary : " <<
          "boundary vec is empty!" << std::endl;

        return false;
    }

    for(EasyBoundary &boundary : boundary_vec_)
    {
        if(boundary.is_outer_boundary)
        {
            if(!boundary.boundary.setAntiClockWise())
            {
                std::cout << "SpaceController::updateBoundary : " <<
                  "setAntiClockWise failed!" << std::endl;

                return false;
            }
        }
        else
        {
            if(!boundary.boundary.setClockWise())
            {
                std::cout << "SpaceController::updateBoundary : " <<
                  "setAntiClockWise failed!" << std::endl;

                return false;
            }
        }
    }

    return true;
}

bool SpaceController::updateRoomConnection()
{
    if(!updateSortedRoomLineVec())
    {
        std::cout << "SpaceController::updateSpace : " <<
          "updateSortedRoomLineVec failed!" << std::endl;

        return false;
    }

    if(!updateRoomLineVecSize())
    {
        std::cout << "SpaceController::updateSpace : " <<
          "updateRoomLineVecSize failed!" << std::endl;

        return false;
    }

    room_boundary_point_vec_.resize(room_vec_.size(), EasyBoundaryPoint());
    room_boundary_line_vec_.resize(room_vec_.size(), EasyBoundaryLine());

    room_line_boundary_point_vec_.resize(room_line_vec_.size(), EasyBoundaryPoint());
    room_line_boundary_line_vec_.resize(room_line_vec_.size(), EasyBoundaryLine());

    return true;
}

bool SpaceController::updateRoom()
{
    if(!updateRoomPosition())
    {
        std::cout << "SpaceController::updateRoom : " <<
          "updateRoomPosition failed!" << std::endl;

        return false;
    }

    if(!updateRoomBoundary())
    {
        std::cout << "SpaceController::updateRoom : " <<
          "updateRoomBoundary failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::outputRoomLineVec()
{
    if(room_line_vec_.size() == 0)
    {
        return true;
    }

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

bool SpaceController::outputRoomLineBoundaryPointVec()
{
    if(room_line_boundary_point_vec_.size() == 0)
    {
        return true;
    }

    for(const EasyBoundaryPoint &boundary_point : room_line_boundary_point_vec_)
    {
        if(!outputBoundaryPoint(boundary_point))
        {
            std::cout << "SpaceController::outputRoomLineBoundaryPointVec : " <<
              "outputBoundaryPoint failed!" << std::endl;

            return false;
        }
    }
    
    return true;
}

bool SpaceController::outputRoomBoundaryPointVec()
{
    if(room_boundary_point_vec_.size() == 0)
    {
        return true;
    }

    for(const EasyBoundaryPoint &boundary_point : room_boundary_point_vec_)
    {
        if(!outputBoundaryPoint(boundary_point))
        {
            std::cout << "SpaceController::outputRoomBoundaryPointVec : " <<
              "outputBoundaryPoint failed!" << std::endl;

            return false;
        }
    }
 
    return true;
}

bool SpaceController::showSpace()
{
    initSpaceImage();

    drawBoundary();

    // drawRoomLinePosition();

    // drawRoomPosition();

    drawRoomBoundary();

    showSpaceImage();

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

bool SpaceController::updateSortedRoomLineVec()
{
    room_line_vec_.clear();

    if(room_vec_.size() == 0)
    {
        std::cout << "SpaceController::updateSortedRoomLineVec : " <<
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
                std::cout << "SpaceController::updateSortedRoomLineVec : " <<
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

    room_line.target_width = 0;

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

bool SpaceController::getRoomLineBoundaryPointParam(
    const EasyRoomLine &room_line,
    const EasyBoundary &boundary,
    const size_t &room_idx,
    const size_t &boundary_line_idx,
    const float &boundary_line_param,
    float &room_line_boundary_point_param)
{
    room_line_boundary_point_param = -1;

    const float boundary_line_length = EasyComputation::pointDist(
        boundary.boundary.point_list[boundary_line_idx],
        boundary.boundary.point_list[(boundary_line_idx + 1) % boundary.boundary.point_list.size()]);

    const float &room_line_target_width = room_line.target_width;

    float room_target_width_sum_before = 0;

    for(const size_t &linear_room_idx : room_line.sorted_room_idx_line)
    {
        if(linear_room_idx == room_idx)
        {
            break;
        }

        room_target_width_sum_before += room_vec_[linear_room_idx].target_width;
    }

    room_target_width_sum_before += 0.5 * room_vec_[room_idx].target_width;

    const float room_target_width_sum_before_param = room_target_width_sum_before / boundary_line_length;

    const float room_line_target_width_param = room_line_target_width / boundary_line_length;

    room_line_boundary_point_param =
      boundary_line_param - room_target_width_sum_before_param + 0.5 * room_line_target_width_param;

    room_line_boundary_point_param = std::fmax(room_line_boundary_point_param, 0);
    room_line_boundary_point_param = std::fmin(room_line_boundary_point_param, 1);

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

    EasyBoundaryPoint &room_line_boundary_point = room_line_boundary_point_vec_[room_line_idx];

    if(!room_line_boundary_point.setPositionParam(
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

bool SpaceController::updateRoomRealWidthOnRoomLine(
    const size_t &room_line_idx)
{
    if(room_line_idx >= room_line_vec_.size())
    {
        std::cout << "SpaceController::updateRoomRealWidthOnRoomLine : " <<
          "room line idx out of range!" << std::endl;

        return false;
    }

    const EasyRoomLine &room_line = room_line_vec_[room_line_idx];

    float room_target_width_sum = 0;
    for(const size_t &room_idx : room_line.sorted_room_idx_line)
    {
        room_target_width_sum += room_vec_[room_idx].target_width;
    }

    float room_real_width_scale = room_line.real_width / room_target_width_sum;

    for(const size_t &room_idx : room_line.sorted_room_idx_line)
    {
        EasyRoom &room = room_vec_[room_idx];

        room.real_width = room_real_width_scale * room.target_width;
    }

    return true;
}

bool SpaceController::updateRoomRealHeightOnRoomLine(
    const size_t &room_line_idx)
{
    if(room_line_idx >= room_line_vec_.size())
    {
        std::cout << "SpaceController::updateRoomRealHeightOnRoomLine : " <<
          "room line idx out of range!" << std::endl;

        return false;
    }

    const EasyRoomLine &room_line = room_line_vec_[room_line_idx];

    for(const size_t &room_idx : room_line.sorted_room_idx_line)
    {
        EasyRoom &room = room_vec_[room_idx];

        room.real_height = room_line.real_height;
    }

    return true;
}

bool SpaceController::updateRoomBoundaryParam(
    const size_t &room_line_idx)
{
    if(room_line_idx >= room_line_vec_.size())
    {
        std::cout << "SpaceController::updateRoomBoundaryParam : " <<
          "room line idx out of range!" << std::endl;

        return false;
    }

    if(room_line_idx >= room_line_boundary_point_vec_.size())
    {
        std::cout << "SpaceController::updateRoomBoundaryParam : " <<
          "room line boundary point not found!" << std::endl;

        return false;
    }

    if(!room_line_boundary_point_vec_[room_line_idx].is_valid)
    {
        std::cout << "SpaceController::updateRoomBoundaryParam : " <<
          "room-line-" << room_line_idx << " not valid!" << std::endl;

        return true;
    }

    EasyBoundaryPoint &boundary_point = room_line_boundary_point_vec_[room_line_idx];
    EasyRoomLine &room_line = room_line_vec_[room_line_idx];
    EasyBoundaryLine &room_line_boundary_line = room_line_boundary_line_vec_[room_line_idx];

    const size_t &boundary_idx = boundary_point.boundary_idx;
    const size_t &boundary_line_idx = boundary_point.boundary_line_idx;
    float &boundary_line_param = boundary_point.boundary_line_param;

    const EasyBoundary &boundary = boundary_vec_[boundary_idx];

    const EasyPoint2D &boundary_start_point = boundary.boundary.point_list[boundary_line_idx];
    const EasyPoint2D &boundary_end_point =
      boundary.boundary.point_list[(boundary_line_idx + 1) % boundary.boundary.point_list.size()];

    const float boundary_line_length =
      EasyComputation::pointDist(boundary_start_point, boundary_end_point);

    if(room_line.target_width >= boundary_line_length)
    {
        room_line.real_width = boundary_line_length;

        boundary_line_param = 0.5;


        room_line_boundary_line.setStartPointParam(
            boundary_idx,
            boundary_line_idx,
            0);

        room_line_boundary_line.setEndPointParam(
            boundary_idx,
            boundary_line_idx,
            1);

        room_line_boundary_line.updatePointPosition(boundary_vec_);
    }
    else
    {
        room_line.real_width = room_line.target_width;

        const float half_room_line_target_width_param =
          0.5 * room_line.target_width / boundary_line_length;

        const float room_line_target_param_min =
          boundary_line_param - half_room_line_target_width_param;

        if(room_line_target_param_min < 0)
        {
            boundary_line_param = half_room_line_target_width_param;
        }
        else
        {
            const float room_line_target_param_max =
              boundary_line_param + half_room_line_target_width_param;

            if(room_line_target_param_max > 1)
            {
                boundary_line_param = 1.0 - half_room_line_target_width_param;
            }
        }

        room_line_boundary_line.setStartPointParam(
            boundary_idx,
            boundary_line_idx,
            boundary_line_param - half_room_line_target_width_param);

        room_line_boundary_line.setEndPointParam(
            boundary_idx,
            boundary_line_idx,
            boundary_line_param + half_room_line_target_width_param);

        room_line_boundary_line.updatePointPosition(boundary_vec_);
    }

    if(!updateRoomRealWidthOnRoomLine(room_line_idx))
    {
        std::cout << "SpaceController::updateRoomBoundaryParam : " <<
          "updateRoomRealWidthOnRoomLine failed!" << std::endl;

        return false;
    }

    const float room_line_real_width_param =
      room_line.real_width / boundary_line_length;

    const float room_line_real_param_min =
      boundary_line_param - 0.5 * room_line_real_width_param;

    float current_room_real_param_min = room_line_real_param_min;

    for(const size_t &room_idx : room_line.sorted_room_idx_line)
    {
        EasyBoundaryPoint &room_boundary_point = room_boundary_point_vec_[room_idx];
        EasyBoundaryLine &room_boundary_line = room_boundary_line_vec_[room_idx];

        const EasyRoom &room = room_vec_[room_idx];

        const float room_real_width_param = room.real_width / boundary_line_length;

        room_boundary_point.setPositionParam(
            boundary_idx,
            boundary_line_idx,
            current_room_real_param_min + 0.5 * room_real_width_param);

        room_boundary_point.updatePosition(boundary_vec_);

        room_boundary_line.setStartPointParam(
            boundary_idx,
            boundary_line_idx,
            current_room_real_param_min);

        current_room_real_param_min += room_real_width_param;

        room_boundary_line.setEndPointParam(
            boundary_idx,
            boundary_line_idx,
            current_room_real_param_min);

        room_boundary_line.updatePointPosition(boundary_vec_);
    }

    room_line.real_height = room_line.target_area / room_line.real_width;

    if(!updateRoomRealHeightOnRoomLine(room_line_idx))
    {
        std::cout << "SpaceController::updateRoomBoundaryParam : " <<
          "updateRoomRealHeightOnRoomLine failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::updateAllRoomBoundaryParam()
{
    if(room_line_vec_.size() == 0)
    {
        std::cout << "SpaceController::updateAllRoomBoundaryParam : " <<
          "room line vec is empty!" << std::endl;

        return true;
    }

    for(size_t i = 0; i < room_line_vec_.size(); ++i)
    {
        if(!updateRoomBoundaryParam(i))
        {
            std::cout << "SpaceController::updateAllRoomBoundaryParam : " <<
              "updateRoomBoundaryParam failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool SpaceController::updateRoomBoundary(
    const size_t &room_line_idx)
{
    if(room_line_idx >= room_line_vec_.size())
    {
        std::cout << "SpaceController::updateRoomBoundary : " <<
          "room line idx out of range!" << std::endl;

        return false;
    }

    EasyRoomLine &room_line = room_line_vec_[room_line_idx];

    float room_real_area_sum = 0;

    for(const size_t &room_idx : room_line.sorted_room_idx_line)
    {
        EasyRoom &room = room_vec_[room_idx];
        const EasyBoundaryLine &room_boundary_line = room_boundary_line_vec_[room_idx];

        EasyPoint2D room_start_position_vertical_direction;
        EasyPoint2D room_end_position_vertical_direction;

        if(!boundary_vec_[room_boundary_line.line_start_boundary_point.boundary_idx].getVerticalDirection(
              room_boundary_line.line_start_boundary_point.boundary_line_idx,
              room_start_position_vertical_direction))
        {
            std::cout << "SpaceController::updateRoomBoundary : " <<
              "getVerticalDirection failed!" << std::endl;

            return false;
        }

        if(!boundary_vec_[room_boundary_line.line_end_boundary_point.boundary_idx].getVerticalDirection(
              room_boundary_line.line_end_boundary_point.boundary_line_idx,
              room_end_position_vertical_direction))
        {
            std::cout << "SpaceController::updateRoomBoundary : " <<
              "getVerticalDirection failed!" << std::endl;

            return false;
        }

        EasyPoint2D room_start_outer_position;
        EasyPoint2D room_end_outer_position;

        room_start_outer_position.setPosition(
            room_boundary_line.line_start_boundary_point.position.x +
            room.real_height * room_start_position_vertical_direction.x,
            room_boundary_line.line_start_boundary_point.position.y +
            room.real_height * room_start_position_vertical_direction.y);

        room_end_outer_position.setPosition(
            room_boundary_line.line_end_boundary_point.position.x +
            room.real_height * room_end_position_vertical_direction.x,
            room_boundary_line.line_end_boundary_point.position.y +
            room.real_height * room_end_position_vertical_direction.y);

        room.boundary.reset();
        room.boundary.addPoint(room_boundary_line.line_start_boundary_point.position);
        room.boundary.addPoint(room_boundary_line.line_end_boundary_point.position);
        room.boundary.addPoint(room_end_outer_position);
        room.boundary.addPoint(room_start_outer_position);

        room.boundary.setAntiClockWise();

        const float room_real_area = room.boundary.getPolygonArea();

        room.real_area = room_real_area;

        room_real_area_sum += room_real_area;
    }

    room_line.real_area = room_real_area_sum;

    return true;
}

bool SpaceController::updateAllRoomBoundary()
{
    if(room_line_vec_.size() == 0)
    {
        std::cout << "SpaceController::updateAllRoomBoundary : " <<
          "room line vec is empty!" << std::endl;

        return true;
    }

    for(size_t i = 0; i < room_line_vec_.size(); ++i)
    {
        if(!updateRoomBoundary(i))
        {
            std::cout << "SpaceController::updateAllRoomBoundary : " <<
              "updateRoomBoundary failed!" << std::endl;

            return false;
        }
    }

    return true;
}

bool SpaceController::updateRoomPosition()
{
    if(!updateAllRoomBoundaryParam())
    {
        std::cout << "SpaceController::updateSpace : " <<
          "updateAllRoomBoundaryParam failed!" << std::endl;

        return false;
    }

    if(!updateRoomLineBoundaryPointPosition())
    {
        std::cout << "SpaceController::updateSpace : " <<
          "updateRoomLineBoundaryPointPosition failed!" << std::endl;

        return false;
    }

    return true;
}

bool SpaceController::updateRoomBoundary()
{
    if(!updateAllRoomBoundary())
    {
        std::cout << "SpaceController::updateRoomBoundary : " <<
          "updateAllRoomBoundary failed!" << std::endl;

        return false;
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

bool SpaceController::outputBoundaryPoint(
    const EasyBoundaryPoint &boundary_point)
{
    std::cout << "BoundaryPoint : " << std::endl;
    std::cout << "\tboundary_idx = " << boundary_point.boundary_idx << std::endl;
    std::cout << "\tboundary_line_idx = " << boundary_point.boundary_line_idx << std::endl;
    std::cout << "\tboundary_line_param = " << boundary_point.boundary_line_param << std::endl;
    std::cout << "\tposition = [" << boundary_point.position.x << "," << boundary_point.position.y << "]" << std::endl;

    return true;
}

bool SpaceController::initSpaceImage()
{
    x_free_ = 50;
    y_free_ = 50;

    x_min_ = std::numeric_limits<float>::max();
    y_min_ = std::numeric_limits<float>::max();

    for(const EasyBoundary &boundary : boundary_vec_)
    {
        x_min_ = std::fmin(x_min_, boundary.boundary.rect.x_min);
        y_min_ = std::fmin(y_min_, boundary.boundary.rect.y_min);
    }

    return true;
}

bool SpaceController::drawBoundary()
{
    float x_max = std::numeric_limits<float>::min();
    float y_max = std::numeric_limits<float>::min();

    for(const EasyBoundary &boundary : boundary_vec_)
    {
        x_max = std::fmax(x_max, boundary.boundary.rect.x_max);
        y_max = std::fmax(y_max, boundary.boundary.rect.y_max);
    }

    const float &x_diff = x_max - x_min_;
    const float &y_diff = y_max - y_min_;

    size_t image_width = size_t(x_diff) + 2 * x_free_;
    size_t image_height = size_t(y_diff) + 2 * y_free_;

    space_image_ = cv::Mat(image_height, image_width, CV_8UC3);

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
            const EasyPoint2D &next_point =
              boundary_polygon.point_list[(i + 1) % boundary_polygon.point_list.size()];

            cv::Point current_cv_point = cv::Point(
                size_t(current_point.x - x_min_) + x_free_,
                size_t(current_point.y - y_min_) + y_free_);
            cv::Point next_cv_point = cv::Point(
                size_t(next_point.x - x_min_) + x_free_,
                size_t(next_point.y - y_min_) + y_free_);

            cv::line(space_image_, current_cv_point, next_cv_point, cv::Scalar(0, 0, 255), 3);

            std::string text = "b" + std::to_string(i);

            cv::putText(space_image_, text, current_cv_point, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));
        }
    }

    return true;
}

bool SpaceController::drawRoomLinePosition()
{
    if(room_line_boundary_point_vec_.size() == 0)
    {
        std::cout << "SpaceController::drawRoomLinePosition : " <<
          "room line boundary point not found!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < room_line_boundary_point_vec_.size(); ++i)
    {
        const EasyBoundaryPoint &room_line_boundary_point = room_line_boundary_point_vec_[i];

        if(!room_line_boundary_point.is_valid)
        {
            continue;
        }

        const EasyPoint2D &room_line_boundary_point_position =
          room_line_boundary_point.position;

        cv::Point cv_point = cv::Point(
            size_t(room_line_boundary_point_position.x - x_min_) + x_free_,
            size_t(room_line_boundary_point_position.y - y_min_) + y_free_);

        cv::circle(space_image_, cv_point, 3, cv::Scalar(0, 255, 0), 3);

        std::string text = "rl" + std::to_string(i);

        cv::putText(space_image_, text, cv_point, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));
    }

    return true;
}

bool SpaceController::drawRoomPosition()
{
    if(room_boundary_point_vec_.size() == 0)
    {
        std::cout << "SpaceController::drawRoomPosition : " <<
          "room boundary point not found!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < room_boundary_point_vec_.size(); ++i)
    {
        const EasyBoundaryPoint &room_boundary_point = room_boundary_point_vec_[i];

        if(!room_boundary_point.is_valid)
        {
            continue;
        }

        const EasyPoint2D &room_boundary_point_position =
          room_boundary_point.position;

        cv::Point cv_point = cv::Point(
            size_t(room_boundary_point_position.x - x_min_) + x_free_,
            size_t(room_boundary_point_position.y - y_min_) + y_free_);

        cv::circle(space_image_, cv_point, 3, cv::Scalar(255, 0, 0), 3);

        std::string text = "r" + std::to_string(i);

        cv::putText(space_image_, text, cv_point, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));
    }

    return true;
}

bool SpaceController::drawRoomBoundary()
{
    if(room_vec_.size() == 0)
    {
        std::cout << "SpaceController::drawRoomBoundary : " <<
          "room vec is empty!" << std::endl;

        return false;
    }

    for(size_t i = 0; i < room_vec_.size(); ++i)
    {
        const EasyRoom &room = room_vec_[i];

        if(room.boundary.point_list.size() == 0)
        {
            continue;
        }

        float average_x = 0;
        float average_y = 0;

        for(size_t j = 0; j < room.boundary.point_list.size(); ++j)
        {
            const EasyPoint2D &boundary_line_start_point = room.boundary.point_list[j];
            const EasyPoint2D &boundary_line_end_point =
              room.boundary.point_list[(j + 1) % room.boundary.point_list.size()];

            average_x += boundary_line_start_point.x;
            average_y += boundary_line_start_point.y;

            cv::Point cv_start_point = cv::Point(
                size_t(boundary_line_start_point.x - x_min_) + x_free_,
                size_t(boundary_line_start_point.y - y_min_) + y_free_);

            cv::Point cv_end_point = cv::Point(
                size_t(boundary_line_end_point.x - x_min_) + x_free_,
                size_t(boundary_line_end_point.y - y_min_) + y_free_);

            cv::line(space_image_, cv_start_point, cv_end_point, cv::Scalar(0, 255, 0), 3);
        }

        average_x = size_t(average_x / room.boundary.point_list.size() - x_min_) + x_free_;
        average_y = size_t(average_y / room.boundary.point_list.size() - y_min_) + y_free_;

        cv::Point cv_text_point = cv::Point(average_x, average_y);

        std::string text = std::to_string(i);

        cv::putText(space_image_, text, cv_text_point, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));
    }

    return true;
}

bool SpaceController::showSpaceImage()
{
    cv::imshow("space_image", space_image_);
    cv::waitKey(0);

    return true;
}

