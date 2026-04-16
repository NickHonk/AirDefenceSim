cmake_minimum_required(VERSION 3.14) # 3.14 für FetchContent
project(AirDefenseSim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trennen der Kern-Dateien von der main.cpp für GTests
set(CORE_SOURCES
    Target.cpp
    Interceptor.cpp
    SimulationEnvironment.cpp
)

# Normales Simulations-Programm
add_executable(SimulationApp main.cpp ${CORE_SOURCES})

# ==========================================
# GoogleTest Integration
# ==========================================
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
# Windows-spezifischer Fix für C++ Laufzeitbibliotheken
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 
FetchContent_MakeAvailable(googletest)

# ==========================================
# GLM Integration (header-only math library)
# ==========================================
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        master  # Use a stable release tag
)
FetchContent_MakeAvailable(glm)

# Test-Programm: kompilieren einer neuen .exe, die nur aus Test und Kern-Dateien besteht
add_executable(SimulationTests test_interceptor.cpp test_target.cpp ${CORE_SOURCES})

# Einbinden der heruntergeladene GTest-Bibliothek an Test-Programm
target_link_libraries(SimulationTests gtest_main)

# Link GLM to both executables (header-only, so no actual linking—just include paths)
target_link_libraries(SimulationApp glm::glm)
target_link_libraries(SimulationTests glm::glm)