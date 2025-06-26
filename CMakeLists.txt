# Versión mínima de CMake requerida. Buena práctica para asegurar compatibilidad.
cmake_minimum_required(VERSION 3.16)

# Define el nombre del proyecto.
project(DroneRoutePlanner LANGUAGES CXX)

# Establece el estándar de C++ que queremos usar para todo el proyecto.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Añade un ejecutable a nuestro proyecto.
# El primer argumento es el nombre que le daremos al ejecutable.
# Los siguientes son todos los archivos .cpp necesarios para construirlo.
add_executable(drone_app
    main.cpp
    WaypointManager.cpp
    RoutePlanner.cpp
)

# ===================================================================
# TESTING SECTION (with Google Test)
# ===================================================================

# Habilitamos la funcionalidad de pruebas en nuestro proyecto CMake.
enable_testing()

# Incluimos el módulo FetchContent para poder descargar dependencias.
include(FetchContent)

# Declaramos la dependencia de Google Test.
# Le decimos a CMake de dónde descargarla (el repositorio de Git) y qué versión (tag) usar.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.14.0
)

# Hacemos que la dependencia esté disponible.
# Esto efectivamente descargará el código si es necesario.
FetchContent_MakeAvailable(googletest)

# Creamos un nuevo ejecutable para nuestras pruebas.
# Nota que NO incluimos main.cpp aquí.
add_executable(run_tests
    tests/test_route_planner.cpp
    # También necesitamos los archivos de implementación de las clases que queremos probar
    WaypointManager.cpp
    RoutePlanner.cpp
)

# Enlazamos nuestro ejecutable de pruebas con las librerías de Google Test.
# gtest_main incluye la función main() para las pruebas, así no tenemos que escribirla.
target_link_libraries(run_tests
    GTest::gtest_main
)

# Añadimos nuestro ejecutable de pruebas al conjunto de pruebas de CTest.
# CTest es la herramienta de ejecución de pruebas de CMake.
include(GoogleTest)
gtest_discover_tests(run_tests)