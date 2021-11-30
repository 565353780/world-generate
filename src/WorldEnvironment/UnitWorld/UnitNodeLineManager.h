#ifndef UNIT_NODE_LINE_MANAGER_H
#define UNIT_NODE_LINE_MANAGER_H

#include "export_library_global.h"

#include "UnitTree.h"

class LIBRARY_EXPORT UnitNodePosition
{
public:
    UnitNodePosition()
    {
        next_position = nullptr;
        prev_position = nullptr;

        reset();
    }

    bool reset();

    bool outputInfo(
        const size_t &info_level) const;

    float center_param;
    float target_left_param;
    float target_right_param;
    float real_left_param;
    float real_right_param;

    UnitNodePosition* prev_position;
    UnitNodePosition* next_position;
};

class LIBRARY_EXPORT UnitNodeLine
{
public:
    UnitNodeLine()
    {
        position_line = nullptr;
    }
    ~UnitNodeLine();

    bool reset();

    bool findNearestUnusedPosition(
        const UnitNodePosition& new_position,
        float &nearest_unused_left_param,
        float &nearest_unused_right_param);

    bool updateNearestUnusedPosition(
        UnitNodePosition& new_position);

    UnitNodePosition* position_line;
};

class UnitNodeLineManager
{
public:
    UnitNodeLineManager()
    {
    }
    
    bool reset();

    UnitTree unit_tree_;
};

#endif // UNIT_NODE_LINE_MANAGER_H
