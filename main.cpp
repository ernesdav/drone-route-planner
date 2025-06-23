#include <iostream>
#include <vector>
#include "WaypointManager.h"
#include "RoutePlanner.h"

int main() {
    // 1. Crear instancias de nuestras clases principales.
    WaypointManager manager;
    RoutePlanner planner;

    std::cout << "--- Loading Waypoints ---" << std::endl;

    // 2. Cargar los waypoints desde el archivo.
    // Se espera que la línea "a_bad_id..." muestre un warning.
    if (!manager.loadWaypointsFromFile("waypoints.txt")) {
        std::cerr << "Failed to load waypoints. Exiting." << std::endl;
        return 1; // Salir con un código de error.
    }
    std::cout << "Waypoints loaded successfully." << std::endl;
    std::cout << "Total waypoints in manager: " << manager.getTotalWaypoints() << std::endl;

    // 3. Demostrar la funcionalidad de WaypointManager.
    std::cout << "\n--- Testing WaypointManager ---" << std::endl;
    manager.printAllWaypoints();

    // 4. Demostrar la funcionalidad de RoutePlanner.
    std::cout << "\n--- Testing RoutePlanner ---" << std::endl;

    // Calcular la distancia entre dos puntos existentes.
    std::cout << "Calculating distance between LA (101) and NYC (103)..." << std::endl;
    double distance = planner.calculateDistance(101, 103, manager);
    std::cout << "Calculated Distance: " << distance << std::endl;

    // Intentar calcular la distancia con un punto que no existe.
    std::cout << "\nCalculating distance with a non-existent ID (999)..." << std::endl;
    planner.calculateDistance(101, 999, manager); // Se espera un error aquí.

    // Definir y mostrar una ruta válida.
    std::vector<int> route = {101, 104, 103}; // Ruta: LA -> Chicago -> NYC
    planner.printRoute(route, manager);

    // Definir y mostrar una ruta inválida.
    std::vector<int> bad_route = {102, 105, 107}; // 105 no existe (era la línea malformada)
    planner.printRoute(bad_route, manager);

    return 0; // Salir exitosamente.
}