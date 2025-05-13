# Garage Engine

The Garage Engine is a work-in-progress OpenGL project with the objective to learn and understand Graphics Programming in C++. This project began in 2021, and has been an on and off project since.

The ultimate end goal is to develop a complex project with what is learned here! (i.e. a simple game or engine!)

## :star: Features :star:

- Lighting System

    - Support for point, directional, and spot lights

    - Unified shader supporting all three lighting types

    - Phong lighting model implementation

- Custom Math Library

    - C/C++-based vector and matrix math

    - Support for versor (quaternion) operations and transformations

- Model Loading

    - Support for .obj, .fbx, and more using Assimp

    - Handles complex meshes with multiple submeshes and materials

- Texture Handling

    - Integration with stb_image.h for texture loading

    - Support for diffuse, specular, and ambient texture maps

- Camera System

    - Custom C++ camera class with:

    - Mouse-controlled orbiting and FPS modes

    - WASD keyboard navigation

    - Perspective and view matrix control

## Learning Sources

The following sources are what I used to learn OpenGL:

- [Anton's OpenGL 4 Tutorials](https://www.amazon.ca/Antons-OpenGL-Tutorials-Anton-Gerdelan-ebook/dp/B00LAMQYF2) (C focused, lab-like assignments)
- [learnopengl.com](https://learnopengl.com/Model-Loading/Mesh) (C++ focused, step-by-step guides)

## Project Status / DevLog

- Looking light features to mesh objects to support 3 different light modes (point, spot, directional). The shaders exist, just need to write the shaders for the meshes and create a demo!
- Writing and setting up mesh objects can be a hassle to set up. Might need to invest some time in working on an Entity Component System.

## Features To Next

The following are a list of features to implement in the feature

- Entity Component System
- Physics (with an external library like [Bullet Physics](https://github.com/bulletphysics/bullet3))
- Completing Advanced OpenGL and Lighting on [learnopengl.com](https://learnopengl.com/Advanced-OpenGL/Depth-testing)

## Project Playlist:

[<img alt="Project Playlist" width="640px" height="480px" src="https://github.com/megarage9000/openGLProjects/blob/main/thumbnails/thumbnail_1.png" />](https://www.youtube.com/playlist?list=PLoYQN9sSaKPZtNqR3CzW2sLVft5kNCWhi)

   
