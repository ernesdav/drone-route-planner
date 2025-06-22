#include "WaypointManager.h"
#include <fstream>
#include <sstream>
#include <iostream>


WaypointManager::WaypointManager() {
    std::cout << "WaypointManager constructed." << std::endl;
}

bool WaypointManager::loadWaypointsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    int lineCounter = 0;  // util para los mensajes de error
    while (std::getline(inputFile, line))
    {
        lineCounter++;
        // ignorar lineas vacias
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string idStr, latStr, lonStr, name;

        // Extraer cada "celda" del CSV usando la coma como delimitador
        std::getline(ss, idStr, ',');
        std::getline(ss, latStr, ',');
        std::getline(ss, lonStr, ',');
        std::getline(ss, name);

        try
        {
            int id = std::stoi(idStr);
            double lat = std::stod(latStr);
            double lon = std::stod(lonStr);

            allWaypoints.emplace_back(id, lat, lon, name);

            // 3. Actualiza el mapa para búsqueda rápida. El ID es la clave,
            //    y el valor es el índice del nuevo elemento en el vector.
            //    El índice del último elemento es siempre `allWaypoints.size() - 1`.
            waypointIdToIndex[id] = allWaypoints.size() - 1;

        }
        catch(const std::invalid_argument& e)
        {
            // Esto atrapa errores si stoi o stod no pueden convertir el texto.
            std::cerr << "Warning: Malformed line " << lineCounter << ": " << line << ". Skipping." << std::endl;
        } catch (const std::out_of_range& e) {
            // Esto atrapa errores si el número es demasiado grande para el tipo de dato.
            std::cerr << "Warning: Number out of range on line " << lineCounter << ": " << line << ". Skipping." << std::endl;
        }
        
    }

    return true;
}

const Waypoint* WaypointManager::getWaypointById(int id) const {
    
    auto it = waypointIdToIndex.find(id);

    if (it == waypointIdToIndex.end()) {
        return nullptr;
    }
    
    size_t index = it->second;
    return &allWaypoints[index];

}

void WaypointManager::printAllWaypoints() const {
    std::cout << "--- All Loaded Waypoints ---" << std::endl;
    if (allWaypoints.empty()){
        std::cout << "No waypoints to print." << std::endl;
        return;
    }
    for (const auto& wp : allWaypoints) {
        std::cout << "Waypoint ID: " << wp.id << ", Name: " << wp.name << ", Latitude: " << wp.latitude << ", Longitude: " << wp.longitude << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

size_t WaypointManager::getTotalWaypoints() const {
    return allWaypoints.size();
}