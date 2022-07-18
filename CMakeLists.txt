cmake_minimum_required(VERSION 3.0)

project(AstraTesting)

set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

set(CMAKE_CXX_STANDARD 11)

add_library(Commons STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Terminal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Logger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Commons/Config.cpp
        )

target_include_directories(Commons PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Commons/>
        $<INSTALL_INTERFACE:include>
        )

add_subdirectory(${PROJECT_SOURCE_DIR}/third-party/json)
target_link_libraries(Commons nlohmann_json)


add_library(Tests STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/BaseTest.cpp
        )

target_include_directories(Tests PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Tests/>
        $<INSTALL_INTERFACE:include>
        )
target_link_libraries(Tests Commons)

add_executable(${PROJECT_NAME} demo/main.cpp)
target_link_libraries(${PROJECT_NAME} Commons Tests)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(CPackConfig.cmake)

file(COPY ${PROJECT_SOURCE_DIR}/misc/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
