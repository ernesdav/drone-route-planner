# Proyecto 5: Sistema simplificado de gestión de rutas para drones
Este proyecto simula un componente esencial en un sistema de drones: la gestión y planificación de rutas basada en puntos de interés (POI).

### Objetivo General:
Diseñar e implementar un sistema en C++ que sea capaz de:
1. Leer datos de **puntos de interés (Waypoints)** desde un **archivo de texto (CSV simulado)**.
1. Almacenar estos Waypoint de manera eficiente para búsquedas rápidas.
1. Calcular **distancias** entre Waypoints.
1. Generar una representación textual de **rutas** dadas una secuencia de Waypoints.
1. Mantener un **diseño modular y robusto**, preparado para futuras expansiones y contenerización con Docker.

### Componentes del Sistema (Clases y Archivos):
Existen tres componentes principales, cada uno con una responsabilidad clara (Principio de Responsabilidad Única - SRP):
1. 'Waypoint' **(Estructura de Datos Simple)**
  * **Archivo:** 'Waypoint.h'
  * **Responsabilidad:** Representar un único punto de interés con sus datos.
  * **Miembros:**
    * 'int id;' (Identificador único del Waypoint)
    * 'double latitude;' (Latitud del punto)
    * 'double longitude;' (Longitud del punto)
    * 'std::string name;' (Nombre descriptivo del Waypoint)
  * **Métodos:** Un construtor para inicializar sus miembros fácilmente.
1. 'WaypointManager' **(Clase de Gestión de Datos)**
  * **Archivos:** 'WaypointManager.h' (declaración), 'WaypointManager.cpp' (implementación)
  * **Responsabilidad:** Cargar Waypoints desde un archivo, almacenarlos internamente y proporcionar métodos para acceder a ellos de forma eficiente. No se preocupa por la planificación de rutas, solo de los datos de Waypoint.
  * **Miembros Privados:**
    * 'std::vector<Waypoint> allWaypoints;' (Almacena todos los Waypoints en el orden en que se leyeron del archivo. Esto mantiene el orden original).
    * 'std::unordered_map<int, size_t> waypointIdToIndex;' (Un mapa hash para mapear el 'id' de un Waypoint a su índice en 'allWaypoints'. Esto permitirá buscar un Waypoint por su ID en o(1) promedio).
  * **Métodos Públicos:**
    * 'WaypointManager();' (Constructor)
    * 'bool loadWaypointsFromFile(const std::string& filename);'
      * **Tarea de E/S y Parseo:** Abrirá el 'filename' usando 'std::ifstream'.
      * Leerá el archivo **línea por línea**.
      * Cada línea se espera en formato **CSV simplificado:** '"ID,LATITUDE,LONGITUDE,NAME"
        * Ejemplo: '1,34.0522,-118.2437,Dowtown LA"
        * Se tendrá que **parsear** la línea: extraer las partes usando 'std::string::find', 'std::string::substr'.
        * Convertir 'ID' a 'int', 'LATITUDE' y 'LONGITUDE' a 'double' ('std::stoi, std::stod').
        * **Manejor Robusto de Errores:** Si una línea está mal formateada, imprimir un error a 'std::cerr' y saltarla ('continue'), sin detener la carga. Si el archivo no se puede abrir, imprimir un error y retornar 'false'.
      * Por cada línea correctamente parseada, crear un objetvo 'Waypoint' y añadir a 'allWaypoints'.
      * Retornar true si la carga del archivo fue exitosa, 'false' si no se pudo abrir.
    * 'const Waypoint* getWaypointById(int id) const;'
      * Utiliza 'waypointIdToIndex' para encontrar rápidamente el índice.
      * Devuelve un puntero constante al 'Waypoint' en 'allWaypoints' si se encuentra, o 'nullptr' si el 'id' no existe.
    * 'void printAllWaypoints() const;'
      * Imprime todos los detalles de todos los Waypoints cargados.
    * 'size_t getTotalWaypoints() const;
      * Devuelve el número total de Waypoints cargados.
1. 'RoutePlanner' **(Clase de Lógica de Rutas)**
  * **Archivos:** 'RoutePlanner.h' (declaración), 'RoutePlanner.cpp' (implementación)
  * **Responsabilidad:** Realizar cálculos y consultar de rutas. Esta clase **depende** de 'WaypointManager' para obtener los datos de Waypoints, pero no gestiona los datos de Watpoint directamente.
  * **Miembros Privados:** Es posible que solo se necesiten punteros/referencias a otras clases si la dependencia es duradera (en este caso se pasa como argumento a los métodos).
  * **Métodos Públicos:**
    * 'RoutePlanner();' (Constructor)
    * 'double calculateDistance(int id1, int id2, const WaypointManager& manager) const;'
      * Toma los IDs de dos Waypoints y una referencia al 'WaypointManager'.
      * Utiliza 'manager.getWaypointById()' para obtener los objetos 'Waypoint' correspondientes.
      * Calcula la distancia **Euclidiana 2D** entre los dos puntos.
      * Maneja el caso si alguno de los Waypoints no se encuentra (imprime un error y devuelve '0.0' o 'std::numeric_limits<double>::infinity()').
    * 'void printRoute(const std::vector<int>& routeIds, const WaypoinManager& manager) const;'
      * Toma una secuencia de Waypoint IDs que defienen una ruta y una referencia al 'WaypointManager'.
      * Imprime todos los detalles de cada Waypoint en la ruta.
      * Calcula e imprime la **distancia total** de la ruta (sumando las distancias entre Waypoints consecutivos).
      * Maneja el caso si alguno de los Waypoints en la secuencia no se encuentra.