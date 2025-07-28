project(vector-fields)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/**.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
