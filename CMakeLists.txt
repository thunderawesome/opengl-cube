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

# Prevent GLFW from building docs, tests, and examples
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
# Executable
# ------------------------------
add_executable(cube main.cpp)

target_link_libraries(cube PRIVATE
    glad
    glfw
    glm::glm
    OpenGL::GL
)

# ------------------------------
# Find OpenGL (required)
# ------------------------------
find_package(OpenGL REQUIRED)

# ------------------------------
# Copy shaders to the executable's directory (handles multi-config like Debug/Release)
# Uses generator expression to get the correct per-config output dir
# ------------------------------
add_custom_command(
    TARGET cube POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.vert
        $<TARGET_FILE_DIR:cube>/cube.vert
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.frag
        $<TARGET_FILE_DIR:cube>/cube.frag
    COMMENT "Copying shader files to executable directory"
)