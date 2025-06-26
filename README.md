# Proyecto 5: Sistema de Gestión de Rutas para Drones

Este es un proyecto de C++ que simula un sistema simplificado para gestionar y planificar rutas de drones basadas en puntos de interés (Waypoints).

El sistema es capaz de leer waypoints desde un archivo, almacenarlos eficientemente, calcular distancias y planificar rutas. El proyecto está completamente contenerizado con Docker y probado con Google Test.

## Características

- Carga de datos desde archivos de texto formato CSV.
- Almacenamiento eficiente con `std::vector` y `std::unordered_map`.
- Cálculo de distancia euclidiana.
- Manejo robusto de errores de parseo.
- Pruebas unitarias con Google Test.
- Sistema de compilación gestionado por CMake.
- Entorno de ejecución portable gracias a Docker.

## Requisitos

- Un compilador de C++17 (como g++)
- CMake (versión 3.16+)
- Docker (opcional, para ejecución contenerizada)

## Cómo Construir y Ejecutar

### Construcción con CMake

1.  Clona el repositorio: `git clone [URL_DE_TU_REPO]`
2.  Crea un directorio de compilación: `mkdir build && cd build`
3.  Configura el proyecto con CMake: `cmake ..`
4.  Compila el proyecto: `make`

### Ejecución

- **Aplicación Principal:** Desde el directorio `build`, ejecuta `./drone_app`
- **Pruebas Unitarias:** Desde el directorio `build`, ejecuta `./run_tests`

### Ejecución con Docker

1.  Construye la imagen Docker: `docker build -t drone-app-image .`
2.  Ejecuta un contenedor a partir de la imagen: `docker run --rm drone-app-image`