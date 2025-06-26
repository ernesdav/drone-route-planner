#ifndef WAYPOINT_MANAGER_H
#define WAYPOINT_MANAGER_H

#include "Waypoint.h"
#include <vector>
#include <unordered_map>

class WaypointManager {
    friend class RoutePlannerTest_CalculatesDistanceCorrectly_Test;
    friend class RoutePlannerTest_HandlesNonExistentWaypoint_Test;
private:
    std::vector<Waypoint> allWaypoints;
    std::unordered_map<int, size_t> waypointIdToIndex;
public:
    WaypointManager();
    bool loadWaypointsFromFile(const std::string& filename);
    const Waypoint* getWaypointById(int id) const;
    void printAllWaypoints() const;
    size_t getTotalWaypoints() const;
};

#endif