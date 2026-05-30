# Custom C++ 3D Game Engine

A custom-built, 3D game engine developed from scratch in C++. Originally conceived as my Computer Science BSc final-year project, it has evolved into a dedicated passion project focused on clean software architecture, modern C++ paradigms, and scalable engine systems.
Design Philosophy & Architecture

## Core Focus: modularity and system decoupling.

API-Agnostic Rendering Interface: The rendering pipeline is built on an IRenderer interface. The current OpenGLRenderer can be cleanly swapped out for a Vulkan or Metal backend without rewriting the core game loop or scene logic.

Resource Factory Pattern: Asset loading (Models, Textures, Shaders, Cubemaps) is handled via a ResourceManager and ResourceFactory, ensuring that Scene objects remain pure data containers unaware of the underlying file I/O or graphics API.

Modern C++: Extensive use of std::shared_ptr and std::unique_ptr for strict ownership semantics, memory safety, and RAII principles.

## Current Features
### Graphics & Rendering

Forward Rendering Pipeline built on OpenGL 3.3+ (Core Profile).

Advanced Lighting Model: Support for Ambient, Diffuse, and Specular calculations.

Dynamic Lights: Full implementation of Directional lights, Point lights, and Spotlights.

Model Importing: Integration with external mesh data for complex 3D object loading via Assimp.

Environment Rendering: Hardware-accelerated Skybox rendering via Cubemaps.

Material System: Configurable material properties (Albedo mapping, Shininess) per entity.

### Engine Systems

Matrix-based spatial transformations (Translation, Rotation, Scale).

Input Handling: Smooth, decoupled camera control systems (First-person/Free-look).

Basic AABB collision detection and continuous physics stepping.

## Planned Features

Shadow Mapping: Directional shadowmap pass is currently in development.

PBR Materials: Physically Based Rendering support for more realistic surface interactions.

More complex Havok physics integration for rigid body dynamics and collision response.

Audio Backend: A simple, decoupled sound system interface.

Engine Tooling: In-engine debugging UI and custom logging systems.

Multithreading

## Build Instructions

This project uses CMake, and requires SDL2, GLAD, glm, and Assimp to be installed