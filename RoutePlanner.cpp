#include "RoutePlanner.h"
#include "WaypointManager.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>


RoutePlanner::RoutePlanner() {
    std::cout << "RoutePlanner constructed." << std::endl;
}

double RoutePlanner::calculateDistance(int id1, int id2, const WaypointManager& manager) const {
    const Waypoint* wp1 = manager.getWaypointById(id1);
    const Waypoint* wp2 = manager.getWaypointById(id2);

    if (wp1 == nullptr || wp2 == nullptr) {
        if (wp1 == nullptr) {
            std::cerr << "Error: Waypoint with ID " << id1 << " not found." << std::endl;
        }
        if (wp2 == nullptr) {
            std::cerr << "Error: Waypoint with ID " << id2 << " not found." << std::endl;
        }
        // Devolvemos infinito para indicar que el cálculo de distancia no es posible.
        return std::numeric_limits<double>::infinity();
    }
    // 3. Calcular la diferencia en latitud y longitud.
    double lat_diff = wp2->latitude - wp1->latitude;
    double lon_diff = wp2->longitude - wp1->longitude;

    // 4. Aplicar la fórmula de la distancia euclidiana y devolver el resultado.
    return std::sqrt(std::pow(lat_diff, 2) + std::pow(lon_diff, 2));
}

void RoutePlanner::printRoute(const std::vector<int>& routeIds, const WaypointManager& manager) const {
    std::cout << "\n--- Printing Route ---" << std::endl;

    // 1. Manejar casos límite
    if (routeIds.empty()) {
        std::cout << "Route is empty." << std::endl;
        return;
    }

    if (routeIds.size() == 1) {
        const Waypoint* wp = manager.getWaypointById(routeIds[0]);
        if (wp) {
            std::cout << "1. " << wp->name << " (ID: " << wp->id << ")" << std::endl;
        } else {
            // Este caso es poco probable si solo hay un ID, pero es bueno ser robusto.
            std::cerr << "Error: Waypoint with ID " << routeIds[0] << " not found." << std::endl;
        }
        std::cout << "Total Distance: 0.0" << std::endl;
        return;
    }

    // 2. Validar que todos los waypoints existen y listarlos
    std::vector<const Waypoint*> waypoint_path;
    bool route_is_valid = true;
    for (size_t i=0; i < routeIds.size(); ++i) {
        const Waypoint* wp = manager.getWaypointById(routeIds[i]);
        if (wp) {
            std::cout << i+1 << ". " << wp->name << " (ID: " << wp->id << ")" << std::endl;
            waypoint_path.push_back(wp);
        } else {
            std::cerr << "Error: Waypoint with ID " << routeIds[i] << " not found. Route calculation aborted." << std::endl;
            route_is_valid = false;
            break;
        }
    }
    
    std::cout << "----------------------" << std::endl;

    // 3. Si la ruta no es válida, no calculamos la distancia.
    if (!route_is_valid) {
        std::cout << "Total Route Distance: Not possible to calculate." << std::endl;
        return;
    }

    // 4. Calcular la distancia total
    double total_distance = 0.0;
    // Iteramos hasta el penúltimo waypoint para tener siempre un par (i, i+1)
    for (size_t i=0; i < routeIds.size()-1; ++i) {
        total_distance += calculateDistance(routeIds[i], routeIds[i+1], manager);
    }

    std::cout << "Total Route Distance: " << total_distance << std::endl;

}