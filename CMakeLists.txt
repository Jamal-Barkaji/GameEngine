cmake_minimum_required(VERSION 3.31)

project(GameEngine)
set(CMAKE_CXX_STANDARD 17)

set(VCPKG_TARGET_TRIPLET "x64-windows-static")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

add_executable(GameEngine main.cpp
        src/Window.cpp
        include/Window.h
        include/Renderer.h
        src/Renderer.cpp
        include/Loop.h
        src/Loop.cpp
        src/Transformer.cpp
        include/Transformer.h
        include/Camera.h
        src/Camera.cpp
        include/Mesh.h
        src/Mesh.cpp
        include/Shader.h
        src/Shader.cpp)

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(GameEngine PRIVATE
        glad::glad
        SDL2::SDL2 SDL2::SDL2main
        OpenGL::GL
        glm::glm
)

target_include_directories(GameEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)