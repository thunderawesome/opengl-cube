# OpenGL Cube

This is a simple OpenGL project that renders a 3D cube with basic lighting and texture support. It features free-camera movement and mouse look controls, demonstrating core modern OpenGL concepts in C++.

<img width="790" height="640" alt="image" src="https://github.com/user-attachments/assets/1d0d8ae6-31a8-4b54-acbf-bfda3042314c" />


## Features

- **Diffuse and Specular Lighting** – Implements Phong lighting model with directional light.
- **Vertex Colors and Texturing** – Cube uses vertex data with colors and a loaded texture (container.jpg).
- **Camera Controls**:
  - **WASD** keys to move the camera (forward, backward, left, right).
  - **Mouse movement** to look around (pitch and yaw).
- **Input System** – Custom input handling for keyboard and mouse.
- **Shaders** – Vertex and fragment shaders written in GLSL (`cube.vert` and `cube.frag`).
- **Resource Embedding** – Shaders and textures are embedded directly into the binary at build time.

## Technologies & Libraries

- **Languages**: C / C++
- **Graphics API**: OpenGL (modern core profile)
- **Libraries**:
  - [GLM](https://glm.g-truc.net/) – OpenGL Mathematics for vectors, matrices, and projections.
  - [GLAD](https://glad.dav1d.de/) – OpenGL function loader.
  - [STB_IMAGE](https://github.com/nothings/stb) – Single-header image loading library.
- **Build System**: CMake
- **CI/CD**: GitHub Actions (`.github/workflows/`)

## Controls

- **W / A / S / D** – Move camera forward / left / backward / right.
- **Mouse** – Look around (move mouse while window is focused).
- **ESC** – Close the window.

## Building the Project

### Prerequisites

- CMake (3.10 or higher)
- A C++ compiler (g++ / clang / MSVC)
- OpenGL development libraries (e.g., on Ubuntu: `libgl1-mesa-dev`, on macOS: built-in, on Windows: via Visual Studio or MinGW)

### Steps

```bash
git clone https://github.com/thunderawesome/opengl-cube.git
cd opengl-cube
mkdir build
cd build
cmake ..
make    # or `cmake --build .` on Windows/MSVC
```

The executable will be generated in the `build` directory (e.g., `opengl-cube` or `opengl-cube.exe`).

Run it:

```bash
./opengl-cube
```

## Project Structure

- `src/` – Source implementation files.
- `include/` – Header files.
- `main.cpp` – Entry point.
- `cube.vert` / `cube.frag` – GLSL shaders.
- `container.jpg` – Example texture.
- `CMakeLists.txt` – Build configuration, including custom commands to embed resources.

## License

Feel free to use or modify this project for learning purposes. No specific license is currently set.

---

Enjoy experimenting with OpenGL! 🚀
