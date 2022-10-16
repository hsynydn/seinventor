cmake_minimum_required(VERSION 3.23)
project(seinvertor)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(${CMAKE_PROJECT_NAME}exec ${BIN_SOURCE_FILES})
add_dependencies(${CMAKE_PROJECT_NAME}exec lib${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}exec PUBLIC lib${CMAKE_PROJECT_NAME})