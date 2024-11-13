# Light-OpenGL

Light-OpenGL is a project that marks my first steps in graphics programming. The aim of the project is to create an environment for experimenting with various OpenGL features. It is based on the tutorial series **OpenGL - The Cherno**, which has helped me grasp the fundamental concepts of graphics programming.

## Table of Contents

- [Project Description](#project-description)
- [Requirements](#requirements)
- [Arguments](#arguments)

## Project Description

Light-OpenGL is a collection of simple applications and sandboxes that allow for testing various OpenGL functions, such as:

- Drawing basic shapes (quad, hexagon)
- Texture sandbox
- Transformation sandbox
- Shader sandbox

## Requirements

To run the project, you need:

- C++20 or later
- OpenGL libraries
- GLFW (for window and input management)
- GLEW (for managing OpenGL extensions)

## Arguments

- `-t [int]`: Open the test with the specified number.
- `-w [int]`: Set the window width (default: 960).
- `-h [int]`: Set the window height (default: 540).
- `-f`: Open in fullscreen mode.

# Light-OpenGL

Light-OpenGL is a project that marks my first steps in graphics programming. The aim of the project is to create an environment for experimenting with various OpenGL features. It is based on the tutorial series **OpenGL - The Cherno**, which has helped me grasp the fundamental concepts of graphics programming.

## Table of Contents

- [Project Description](#project-description)
- [Requirements](#requirements)
- [Setup](#setup)
- [Arguments](#arguments)


## Project Description

Light-OpenGL is a collection of simple applications and sandboxes that allow for testing various OpenGL functions, such as:

- Drawing basic shapes (quad, hexagon)
- Texture sandbox
- Transformation sandbox
- Shader sandbox

## Requirements

To run the project, you need:

- C++20 or later
- OpenGL libraries
- GLFW (setup for your OS)
- GLEW (setup for your OS)

## Setup

To build the project, you need **Premake** for generating project files.

### Windows

1. Download the `premake5.exe` file.
2. Place it in the `tools/Premake/bin` directory.
3. Run Setup-Windows.bat.

### Linux

1. Download the necessary executable files for Premake.
2. Place them in the `Linux/` folder.
3. Run Setup-Linux.sh.

## Arguments

- `-t [int]`: Open the test with the specified number.
- `-w [int]`: Set the window width (default: 960).
- `-h [int]`: Set the window height (default: 540).
- `-f`: Open in fullscreen mode.