#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <vector>

// Declaración anticipada de WaypointManager.
// Le decimos al compilador "confía en mí, esta clase existe",
// sin necesidad de incluir el archivo .h completo.
class WaypointManager;

class RoutePlanner {
public:
    RoutePlanner();
    double calculateDistance(int id1, int id2, const WaypointManager& manager) const;
    void printRoute(const std::vector<int>& routeIds, const WaypointManager& manager) const;
};

#endif