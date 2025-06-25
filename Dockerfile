# --- ETAPA 1: El Taller de Construcción (Builder) ---
# Usamos una imagen oficial que ya tiene el compilador g++ y las herramientas necesarias.
FROM gcc:latest AS builder

# Establecemos el directorio de trabajo dentro del contenedor.
WORKDIR /app

# Copiamos TODOS los archivos de nuestro proyecto (código fuente) al directorio /app.
# El .dockerignore evitará que se copie la carpeta .git y otros archivos.
COPY . .

# Ejecutamos el comando de compilación que ya conocemos para crear nuestro ejecutable.
# Usamos RUN para ejecutar cualquier comando de shell.
RUN g++ main.cpp WaypointManager.cpp RoutePlanner.cpp -o drone_app -std=c++17 -static

# --- ETAPA 2: El Paquete Final (Production) ---
# Empezamos desde una imagen base de Ubuntu, que es ligera.
FROM ubuntu:latest

# Establecemos el directorio de trabajo.
WORKDIR /app

# Copiamos el archivo de datos que nuestra aplicación necesita.
COPY --from=builder /app/waypoints.txt .

# La magia: Copiamos SOLAMENTE el ejecutable compilado desde la etapa "builder".
COPY --from=builder /app/drone_app .

# El comando que se ejecutará por defecto cuando se inicie un contenedor de esta imagen.
CMD ["./drone_app"]