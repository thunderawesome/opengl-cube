cmake_minimum_required(VERSION 3.16)
project(OpenGLCube LANGUAGES CXX C VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# ------------------------------
# GLM (header-only math library)
# ------------------------------
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

# ------------------------------
# GLFW (window and input)
# ------------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# ------------------------------
# GLAD (OpenGL loader - manual)
# ------------------------------
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)

# ------------------------------
# STB Image (header-only for texture loading)
# ------------------------------
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE include)

# ------------------------------
# Executable - with all refactored source files
# ------------------------------
add_executable(cube
    main.cpp
    Camera.cpp
    Shader.cpp
    Texture.cpp
    Mesh.cpp
    InputSystem.cpp
    Time.cpp
)

target_link_libraries(cube PRIVATE
    glad
    glfw
    glm::glm
    stb_image
    OpenGL::GL
)

find_package(OpenGL REQUIRED)

# Ensure include paths for custom headers, stb_image, and generated shaders
target_include_directories(cube PRIVATE include ${CMAKE_BINARY_DIR})

# ------------------------------
# Embed shaders as C++ strings
# ------------------------------
set(EMBEDDED_SHADERS_HEADER ${CMAKE_BINARY_DIR}/shaders_embedded.h)

add_custom_command(
    OUTPUT ${EMBEDDED_SHADERS_HEADER}
    COMMAND ${CMAKE_COMMAND}
        -D INPUT_VERT=${CMAKE_CURRENT_SOURCE_DIR}/cube.vert
        -D INPUT_FRAG=${CMAKE_CURRENT_SOURCE_DIR}/cube.frag
        -D OUTPUT_HEADER=${EMBEDDED_SHADERS_HEADER}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/embed_shaders.cmake
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/embed_shaders.cmake
    COMMENT "Embedding shaders into C++ header"
)

add_custom_target(embed_shaders DEPENDS ${EMBEDDED_SHADERS_HEADER})
add_dependencies(cube embed_shaders)

# ------------------------------
# Bundle container.jpg with the executable (for local testing and releases)
# ------------------------------
add_custom_command(
    TARGET cube POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/container.jpg
        $<TARGET_FILE_DIR:cube>/container.jpg
    COMMENT "Copying container.jpg to executable directory"
)