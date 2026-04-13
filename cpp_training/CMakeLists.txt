# 1. Definiere die minimal benötigte CMake-Version
cmake_minimum_required(VERSION 3.10)

# 2. Gib deinem Projekt einen Namen (das zeigt Professionalität)
project(AirDefenseSim VERSION 1.0)

# 3. Fordere den modernen C++ Standard an (C++17 ist aktuell ein guter Industrie-Standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. Fasse alle .cpp Dateien zusammen, die kompiliert werden müssen
set(SOURCES
    main.cpp
    Target.cpp
    Interceptor.cpp
    SimulationEnvironment.cpp
)

# 5. Erstelle die ausführbare Datei (Executable) aus den Quellen
add_executable(SimulationApp ${SOURCES})