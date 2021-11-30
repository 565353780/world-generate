#include "UnitNodeLineManager.h"

bool UnitNodePosition::reset()
{
    center_param = -1;
    target_left_param = -1;
    target_right_param = -1;
    real_left_param = -1;
    real_right_param = -1;

    if(next_position != nullptr)
    {
        next_position->reset();

        delete(next_position);
        next_position = nullptr;
    }

    return true;
}

bool UnitNodePosition::outputInfo(
    const size_t &info_level) const
{
    std::string line_start = "";
    for(size_t i = 0; i < info_level; ++i)
    {
        line_start += "\t";
    }

    std::cout << line_start << "UnitNodePosition :\n" <<
      line_start << "\t target_param = [" << target_left_param << "," <<
      center_param << "," <<
      target_right_param << "]\n" <<
      line_start << "\t real_param = [" << real_left_param << "," <<
      real_right_param << "]" << std::endl;

    return true;
}

UnitNodeLine::~UnitNodeLine()
{
    reset();
}

bool UnitNodeLine::reset()
{
    if(position_line != nullptr)
    {
        position_line->reset();

        delete(position_line);
        position_line = nullptr;
    }

    return true;
}

bool UnitNodeLine::findNearestUnusedPosition(
    const UnitNodePosition& new_position,
    float &nearest_unused_left_param,
    float &nearest_unused_right_param)
{
    if(position_line == nullptr)
    {
        nearest_unused_left_param = 0;
        nearest_unused_right_param = 1;

        return true;
    }

    return true;
}

bool UnitNodeLine::updateNearestUnusedPosition(
    UnitNodePosition& new_position)
{
    if(position_line == nullptr)
    {
    }

    return true;
}

bool UnitNodeLineManager::reset()
{
    return true;
}

