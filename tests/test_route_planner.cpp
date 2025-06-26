#include <gtest/gtest.h>
#include "../RoutePlanner.h"
#include "../WaypointManager.h" // Incluimos las clases que vamos a probar

// TEST es una macro de Google Test para definir un caso de prueba.
// El primer argumento es el nombre del "Test Suite" (agrupación de pruebas).
// El segundo argumento es el nombre del Test específico.
TEST(RoutePlannerTest, CalculatesDistanceCorrectly) {
    // ARRANGE: Preparamos el escenario de la prueba.
    WaypointManager manager;
    // Creamos dos waypoints directamente, sin usar un archivo.
    // Un triángulo rectángulo 3-4-5 es perfecto para una prueba, el resultado es exacto.
    manager.allWaypoints.emplace_back(1, 0.0, 0.0, "Origin");
    manager.allWaypoints.emplace_back(2, 3.0, 4.0, "Destination");
    // Actualizamos el mapa manualmente para esta prueba
    manager.waypointIdToIndex[1] = 0;
    manager.waypointIdToIndex[2] = 1;

    RoutePlanner planner;

    // ACT: Ejecutamos la acción que queremos probar.
    double distance = planner.calculateDistance(1, 2, manager);

    // ASSERT: Verificamos que el resultado es el esperado.
    // EXPECT_DOUBLE_EQ comprueba que dos números de punto flotante son iguales.
    EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST(RoutePlannerTest, HandlesNonExistentWaypoint) {
    // ARRANGE
    WaypointManager manager;
    RoutePlanner planner;
    manager.allWaypoints.emplace_back(1, 0.0, 0.0, "Origin");
    manager.waypointIdToIndex[1] = 0;

    // ACT
    double distance = planner.calculateDistance(1, 999, manager); // 999 no existe

    // ASSERT
    // Comprobamos que devuelve infinito, como lo diseñamos.
    EXPECT_EQ(distance, std::numeric_limits<double>::infinity());
}