cmake_minimum_required (VERSION 3.22)

# Vcpkg integration
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project ("AoC23" C CXX)

add_executable (AoC23)
target_sources(AoC23 PRIVATE "AoC23.cpp" "AoC23.hpp")

set_property(TARGET AoC23 PROPERTY CXX_STANDARD 20)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(AoC23 PUBLIC spdlog::spdlog)

