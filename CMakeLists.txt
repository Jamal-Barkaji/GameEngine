cmake_minimum_required(VERSION 3.31)

project(GameEngine)
set(CMAKE_CXX_STANDARD 17)

set(VCPKG_TARGET_TRIPLET "x64-windows-static")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

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
        src/Shader.cpp
        include/Input.h
        src/Input.cpp
        include/Texture.h
        src/Texture.cpp
        include/Light.h
        src/Light.cpp
        include/Material.h
        src/Material.cpp
        include/DirectionalLight.h
        src/DirectionalLight.cpp
        include/PointLight.h
        src/PointLight.cpp
        include/CommonValues.h
        include/SpotLight.h
        src/SpotLight.cpp
        include/Model.h
        src/Model.cpp)

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

target_link_libraries(GameEngine PRIVATE
        glad::glad
        SDL2::SDL2 SDL2::SDL2main
        OpenGL::GL
        glm::glm
        assimp::assimp
)

target_include_directories(GameEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)