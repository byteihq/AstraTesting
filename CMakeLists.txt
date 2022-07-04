cmake_minimum_required(VERSION 3.0)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
    SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(AstraTesting)

set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCONSOLE_OUTPUT)
add_definitions(-DFILE_OUTPUT)

hunter_add_package(Boost COMPONENTS program_options)
find_package(Boost CONFIG REQUIRED program_options)

add_library(Commons STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Terminal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Logger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Utils.cpp
        )

target_include_directories(Commons PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Commons/>
        $<INSTALL_INTERFACE:include>
        )

add_executable(${PROJECT_NAME} demo/main.cpp)

target_link_libraries(${PROJECT_NAME} Commons Boost::program_options)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(CPackConfig.cmake)
