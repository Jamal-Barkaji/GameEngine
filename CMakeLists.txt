cmake_minimum_required(VERSION 3.20)

# --- Cross-Platform Environment Setup ---
if(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "" FORCE)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    if(APPLE)
        set(VCPKG_TARGET_TRIPLET "arm64-osx" CACHE STRING "" FORCE)
    endif()
endif()

project(GameEngine)
set(CMAKE_CXX_STANDARD 17)

# --- List non-code files so they appear in the IDE Tree ---
set(SHADER_FILES
    Shaders/shader.frag
    Shaders/shader.vert
    Shaders/skybox.frag
    Shaders/skybox.vert
    Shaders/directional_shadow_map.frag
    Shaders/directional_shadow_map.vert
        include/OpenGLCubeMap.h
        src/OpenGLCubeMap.cpp
        include/ICubeMap.h
)

# --- Executable ---
add_executable(GameEngine
    main.cpp
    ${SHADER_FILES}
    src/Window.cpp
    include/Window.h
    include/OpenGLRenderer.h
    src/OpenGLRenderer.cpp
    include/Loop.h
    src/Loop.cpp
    src/Transformer.cpp
    include/Transformer.h
    include/Camera.h
    src/Camera.cpp
    include/OpenGLMesh.h
    src/OpenGLMesh.cpp
    include/OpenGLShader.h
    src/OpenGLShader.cpp
    include/Input.h
    src/Input.cpp
    include/OpenGLTexture.h
    src/OpenGLTexture.cpp
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
    src/Model.cpp
    include/OpenGLShadowMap.h
    src/OpenGLShadowMap.cpp
    include/ResourceManager.h
    src/ResourceManager.cpp
    include/Scene.h
    src/Scene.cpp
    include/RenderObject.h
    include/GeometryGenerator.h
    src/GeometryGenerator.cpp
    include/PhysicsObject.h
    include/PhysicsSystem.h
    src/PhysicsSystem.cpp
    include/Entity.h
    include/Skybox.h
    src/Skybox.cpp
    src/stb_image.cpp
    include/IRenderer.h
    include/IShader.h
    include/ITexture.h
    include/IMesh.h
    include/IResourceFactory.h
    include/OpenGLResourceFactory.h
    src/OpenGLResourceFactory.cpp
    include/IShadowMap.h
    include/BaseMesh.h
    src/BaseMesh.cpp
    include/OpenGLOmniShadowMap.h
    src/OpenGLOmniShadowMap.cpp
    Shaders/omni_shadow_map.vert
    Shaders/omni_shadow_map.frag
    Shaders/omni_shadow_map.geom

)

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

target_link_libraries(GameEngine PRIVATE
    glad::glad
    SDL2::SDL2
    $<$<PLATFORM_ID:Windows>:SDL2::SDL2main>
    OpenGL::GL
    glm::glm
    assimp::assimp
)

target_include_directories(GameEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- Assets and Shaders Copying ---
# Custom commands used to ensure files are re-copied when changed
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "${CMAKE_CURRENT_BINARY_DIR}/Assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
        "${CMAKE_CURRENT_BINARY_DIR}/Shaders"
    COMMENT "Copying Assets and Shaders to build directory..."
)