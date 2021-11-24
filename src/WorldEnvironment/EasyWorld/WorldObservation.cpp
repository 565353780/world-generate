#include "WorldObservation.h"

bool WorldObservation::reset()
{
    outerwall_boundary_polygon_vec_.clear();
    innerwall_boundary_polygon_vec_.clear();
    roomcontainer_boundary_polygon_vec_.clear();
    wallroom_boundary_polygon_vec_.clear();
    freeroom_boundary_polygon_vec_.clear();
    door_boundary_polygon_vec_.clear();
    window_boundary_polygon_vec_.clear();
    team_boundary_polygon_vec_.clear();
    person_boundary_polygon_vec_.clear();
    furniture_boundary_polygon_vec_.clear();

    return true;
}

bool WorldObservation::getObservation(
    WorldController& world_controller)
{
    if(!getOuterWallBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getOuterWallBoundaryPolygon failed!\n";

        return false;
    }

    if(!getInnerWallBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getInnerWallBoundaryPolygon failed!\n";

        return false;
    }

    if(!getRoomContainerBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getRoomContainerBoundaryPolygon failed!\n";

        return false;
    }

    if(!getWallRoomBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getWallRoomBoundaryPolygon failed!\n";

        return false;
    }

    if(!getFreeRoomBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getFreeRoomBoundaryPolygon failed!\n";

        return false;
    }

    if(!getDoorBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getDoorBoundaryPolygon failed!\n";

        return false;
    }

    if(!getWindowBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getWindowBoundaryPolygon failed!\n";

        return false;
    }

    if(!getTeamBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getTeamBoundaryPolygon failed!\n";

        return false;
    }

    if(!getPersonBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getPersonBoundaryPolygon failed!\n";

        return false;
    }

    if(!getFurnitureBoundaryPolygon(world_controller))
    {
        std::cout << "WorldObservation::getObservation :\n" <<
          "getFurnitureBoundaryPolygon failed!\n";

        return false;
    }

    return true;
}

bool WorldObservation::getOuterWallBoundaryPolygon(
    WorldController& world_controller)
{
    outerwall_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> outerwall_space_node_vec;

    if(!world_controller.getOuterWallSpaceNodeVec(outerwall_space_node_vec))
    {
        std::cout << "WorldObservation::getOuterWallBoundaryPolygon :\n" <<
          "getOuterWallSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* outerwall_space_node : outerwall_space_node_vec)
    {
        if(outerwall_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &outerwall_space_polygon =
          outerwall_space_node->getBoundaryPolygon();

        if(outerwall_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getOuterWallBoundaryPolygon :\n" <<
              "outerwall boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D outerwall_space_polygon_in_world;

        for(const EasyPoint2D& outerwall_space_polygon_point :
            outerwall_space_polygon.point_list)
        {
            EasyPoint2D outerwall_space_boundary_point_in_world;

            if(!outerwall_space_node->getPointInWorld(
                  outerwall_space_polygon_point,
                  outerwall_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getOuterWallBoundaryPolygon :\n" <<
                  "getPointInWorld for outerwall space polygon point failed!\n";

                return false;
            }

            outerwall_space_polygon_in_world.addPoint(
                outerwall_space_boundary_point_in_world);
        }

        outerwall_boundary_polygon_vec_.emplace_back(outerwall_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getInnerWallBoundaryPolygon(
    WorldController& world_controller)
{
    innerwall_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> innerwall_space_node_vec;

    if(!world_controller.getInnerWallSpaceNodeVec(innerwall_space_node_vec))
    {
        std::cout << "WorldObservation::getInnerWallBoundaryPolygon :\n" <<
          "getInnerWallSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* innerwall_space_node : innerwall_space_node_vec)
    {
        if(innerwall_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &innerwall_space_polygon =
          innerwall_space_node->getBoundaryPolygon();

        if(innerwall_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getInnerWallBoundaryPolygon :\n" <<
              "innerwall boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D innerwall_space_polygon_in_world;

        for(const EasyPoint2D& innerwall_space_polygon_point :
            innerwall_space_polygon.point_list)
        {
            EasyPoint2D innerwall_space_boundary_point_in_world;

            if(!innerwall_space_node->getPointInWorld(
                  innerwall_space_polygon_point,
                  innerwall_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getInnerWallBoundaryPolygon :\n" <<
                  "getPointInWorld for innerwall space polygon point failed!\n";

                return false;
            }

            innerwall_space_polygon_in_world.addPoint(
                innerwall_space_boundary_point_in_world);
        }

        innerwall_boundary_polygon_vec_.emplace_back(innerwall_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getRoomContainerBoundaryPolygon(
    WorldController& world_controller)
{
    roomcontainer_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> roomcontainer_space_node_vec;

    if(!world_controller.getRoomContainerSpaceNodeVec(roomcontainer_space_node_vec))
    {
        std::cout << "WorldObservation::getRoomContainerBoundaryPolygon :\n" <<
          "getRoomContainerSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* roomcontainer_space_node : roomcontainer_space_node_vec)
    {
        if(roomcontainer_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &roomcontainer_space_polygon =
          roomcontainer_space_node->getBoundaryPolygon();

        if(roomcontainer_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getRoomContainerBoundaryPolygon :\n" <<
              "roomcontainer boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D roomcontainer_space_polygon_in_world;

        for(const EasyPoint2D& roomcontainer_space_polygon_point :
            roomcontainer_space_polygon.point_list)
        {
            EasyPoint2D roomcontainer_space_boundary_point_in_world;

            if(!roomcontainer_space_node->getPointInWorld(
                  roomcontainer_space_polygon_point,
                  roomcontainer_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getRoomContainerBoundaryPolygon :\n" <<
                  "getPointInWorld for roomcontainer space polygon point failed!\n";

                return false;
            }

            roomcontainer_space_polygon_in_world.addPoint(
                roomcontainer_space_boundary_point_in_world);
        }

        roomcontainer_boundary_polygon_vec_.emplace_back(roomcontainer_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getWallRoomBoundaryPolygon(
    WorldController& world_controller)
{
    wallroom_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> wallroom_space_node_vec;

    if(!world_controller.getWallRoomSpaceNodeVec(wallroom_space_node_vec))
    {
        std::cout << "WorldObservation::getWallRoomBoundaryPolygon :\n" <<
          "getWallRoomSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* wallroom_space_node : wallroom_space_node_vec)
    {
        if(wallroom_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &wallroom_space_polygon =
          wallroom_space_node->getBoundaryPolygon();

        if(wallroom_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getWallRoomBoundaryPolygon :\n" <<
              "wallroom boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D wallroom_space_polygon_in_world;

        for(const EasyPoint2D& wallroom_space_polygon_point :
            wallroom_space_polygon.point_list)
        {
            EasyPoint2D wallroom_space_boundary_point_in_world;

            if(!wallroom_space_node->getPointInWorld(
                  wallroom_space_polygon_point,
                  wallroom_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getWallRoomBoundaryPolygon :\n" <<
                  "getPointInWorld for wallroom space polygon point failed!\n";

                return false;
            }

            wallroom_space_polygon_in_world.addPoint(
                wallroom_space_boundary_point_in_world);
        }

        wallroom_boundary_polygon_vec_.emplace_back(wallroom_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getFreeRoomBoundaryPolygon(
    WorldController& world_controller)
{
    freeroom_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> freeroom_space_node_vec;

    if(!world_controller.getFreeRoomSpaceNodeVec(freeroom_space_node_vec))
    {
        std::cout << "WorldObservation::getFreeRoomBoundaryPolygon :\n" <<
          "getFreeRoomSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* freeroom_space_node : freeroom_space_node_vec)
    {
        if(freeroom_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &freeroom_space_polygon =
          freeroom_space_node->getBoundaryPolygon();

        if(freeroom_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getFreeRoomBoundaryPolygon :\n" <<
              "freeroom boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D freeroom_space_polygon_in_world;

        for(const EasyPoint2D& freeroom_space_polygon_point :
            freeroom_space_polygon.point_list)
        {
            EasyPoint2D freeroom_space_boundary_point_in_world;

            if(!freeroom_space_node->getPointInWorld(
                  freeroom_space_polygon_point,
                  freeroom_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getFreeRoomBoundaryPolygon :\n" <<
                  "getPointInWorld for freeroom space polygon point failed!\n";

                return false;
            }

            freeroom_space_polygon_in_world.addPoint(
                freeroom_space_boundary_point_in_world);
        }

        freeroom_boundary_polygon_vec_.emplace_back(freeroom_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getDoorBoundaryPolygon(
    WorldController& world_controller)
{
    door_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> door_space_node_vec;

    if(!world_controller.getDoorSpaceNodeVec(door_space_node_vec))
    {
        std::cout << "WorldObservation::getDoorBoundaryPolygon :\n" <<
          "getDoorSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* door_space_node : door_space_node_vec)
    {
        if(door_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &door_space_polygon =
          door_space_node->getBoundaryPolygon();

        if(door_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getDoorBoundaryPolygon :\n" <<
              "door boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D door_space_polygon_in_world;

        for(const EasyPoint2D& door_space_polygon_point :
            door_space_polygon.point_list)
        {
            EasyPoint2D door_space_boundary_point_in_world;

            if(!door_space_node->getPointInWorld(
                  door_space_polygon_point,
                  door_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getDoorBoundaryPolygon :\n" <<
                  "getPointInWorld for door space polygon point failed!\n";

                return false;
            }

            door_space_polygon_in_world.addPoint(
                door_space_boundary_point_in_world);
        }

        door_boundary_polygon_vec_.emplace_back(door_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getWindowBoundaryPolygon(
    WorldController& world_controller)
{
    window_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> window_space_node_vec;

    if(!world_controller.getWindowSpaceNodeVec(window_space_node_vec))
    {
        std::cout << "WorldObservation::getWindowBoundaryPolygon :\n" <<
          "getWindowSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* window_space_node : window_space_node_vec)
    {
        if(window_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &window_space_polygon =
          window_space_node->getBoundaryPolygon();

        if(window_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getWindowBoundaryPolygon :\n" <<
              "window boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D window_space_polygon_in_world;

        for(const EasyPoint2D& window_space_polygon_point :
            window_space_polygon.point_list)
        {
            EasyPoint2D window_space_boundary_point_in_world;

            if(!window_space_node->getPointInWorld(
                  window_space_polygon_point,
                  window_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getWindowBoundaryPolygon :\n" <<
                  "getPointInWorld for window space polygon point failed!\n";

                return false;
            }

            window_space_polygon_in_world.addPoint(
                window_space_boundary_point_in_world);
        }

        window_boundary_polygon_vec_.emplace_back(window_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getTeamBoundaryPolygon(
    WorldController& world_controller)
{
    team_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> team_space_node_vec;

    if(!world_controller.getTeamSpaceNodeVec(team_space_node_vec))
    {
        std::cout << "WorldObservation::getTeamBoundaryPolygon :\n" <<
          "getTeamSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* team_space_node : team_space_node_vec)
    {
        if(team_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &team_space_polygon =
          team_space_node->getBoundaryPolygon();

        if(team_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getTeamBoundaryPolygon :\n" <<
              "team boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D team_space_polygon_in_world;

        for(const EasyPoint2D& team_space_polygon_point :
            team_space_polygon.point_list)
        {
            EasyPoint2D team_space_boundary_point_in_world;

            if(!team_space_node->getPointInWorld(
                  team_space_polygon_point,
                  team_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getTeamBoundaryPolygon :\n" <<
                  "getPointInWorld for team space polygon point failed!\n";

                return false;
            }

            team_space_polygon_in_world.addPoint(
                team_space_boundary_point_in_world);
        }

        team_boundary_polygon_vec_.emplace_back(team_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getPersonBoundaryPolygon(
    WorldController& world_controller)
{
    person_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> person_space_node_vec;

    if(!world_controller.getPersonSpaceNodeVec(person_space_node_vec))
    {
        std::cout << "WorldObservation::getPersonBoundaryPolygon :\n" <<
          "getPersonSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* person_space_node : person_space_node_vec)
    {
        if(person_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &person_space_polygon =
          person_space_node->getBoundaryPolygon();

        if(person_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getPersonBoundaryPolygon :\n" <<
              "person boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D person_space_polygon_in_world;

        for(const EasyPoint2D& person_space_polygon_point :
            person_space_polygon.point_list)
        {
            EasyPoint2D person_space_boundary_point_in_world;

            if(!person_space_node->getPointInWorld(
                  person_space_polygon_point,
                  person_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getPersonBoundaryPolygon :\n" <<
                  "getPointInWorld for person space polygon point failed!\n";

                return false;
            }

            person_space_polygon_in_world.addPoint(
                person_space_boundary_point_in_world);
        }

        person_boundary_polygon_vec_.emplace_back(person_space_polygon_in_world);
    }

    return true;
}

bool WorldObservation::getFurnitureBoundaryPolygon(
    WorldController& world_controller)
{
    furniture_boundary_polygon_vec_.clear();

    std::vector<EasyNode*> furniture_space_node_vec;

    if(!world_controller.getFurnitureSpaceNodeVec(furniture_space_node_vec))
    {
        std::cout << "WorldObservation::getFurnitureBoundaryPolygon :\n" <<
          "getFurnitureSpaceNodeVec failed!\n";

        return false;
    }

    for(EasyNode* furniture_space_node : furniture_space_node_vec)
    {
        if(furniture_space_node == nullptr)
        {
            continue;
        }

        const EasyPolygon2D &furniture_space_polygon =
          furniture_space_node->getBoundaryPolygon();

        if(furniture_space_polygon.point_list.size() == 0)
        {
            std::cout << "WorldObservation::getFurnitureBoundaryPolygon :\n" <<
              "furniture boundary polygon is empty!\n";

            return false;
        }

        EasyPolygon2D furniture_space_polygon_in_world;

        for(const EasyPoint2D& furniture_space_polygon_point :
            furniture_space_polygon.point_list)
        {
            EasyPoint2D furniture_space_boundary_point_in_world;

            if(!furniture_space_node->getPointInWorld(
                  furniture_space_polygon_point,
                  furniture_space_boundary_point_in_world))
            {
                std::cout << "WorldObservation::getFurnitureBoundaryPolygon :\n" <<
                  "getPointInWorld for furniture space polygon point failed!\n";

                return false;
            }

            furniture_space_polygon_in_world.addPoint(
                furniture_space_boundary_point_in_world);
        }

        furniture_boundary_polygon_vec_.emplace_back(furniture_space_polygon_in_world);
    }

    return true;
}

