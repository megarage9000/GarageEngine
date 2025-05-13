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

    - Support for .obj, .fbx, and more using [Assimp](https://github.com/assimp/assimp)

    - Handles complex meshes with multiple submeshes and materials

- Texture Handling

    - Integration with [stb_image.h](https://github.com/nothings/stb) for texture loading

    - Support for diffuse, specular, and ambient texture maps

- Camera System

    - Custom C++ camera class with:

    - Mouse-controlled orbiting and FPS modes

    - WASD keyboard navigation

    - Perspective and view matrix control

## :open_file_folder: Folder Index :open_file_folder:

### In the Root folder, there are these following folders:

- `OpenGLCommon`

A folder containing `.cpp`, `.h`, and shader (i.e. `.vert` and `.frag`) files commonly used on all projects. However this folder may be removed due to the lack of common `.cpp` and `.h` files.

- `thumbnails`

Used to store images used on this markdown file.

### In the `GarageEngineSolution` folder, there these following folders / visual studio projects:

- `GarageLog/`

A list of functions to handle logging features of the Garage Engine. Mostly written in C-Style C++, and was encouraged by [Anton's OpenGL 4 Tutorials](https://www.amazon.ca/Antons-OpenGL-Tutorials-Anton-Gerdelan-ebook/dp/B00LAMQYF2) to be used in this project.

- `GarageMath/`

A library of C/C++ functions and classes supporting various matrix, vector, and versor/quaternion.operations. The `GarageLinearAlgebra`files introduces the matrix and vector classes, along with matrix and vector operations. The `GarageLinearTransformations` files extend on `GarageLinearAlgebra` to include common linear transformations for OpenGL, as well as quaternions.

This custom `GarageMath/` folder was also encouraged to be developed by [Anton's OpenGL 4 Tutorials](https://www.amazon.ca/Antons-OpenGL-Tutorials-Anton-Gerdelan-ebook/dp/B00LAMQYF2), and is the primary math library for this project.

- `GarageEngineObjects/`

A library containing objects that is used for the project, including the `EngineObject`, `CameraObject` and the `RenderableObject`. Plans for an Entity Componenty System will be take place in this folder.

- `GarageMesh/`

A library containing a `Mesh` and `Model` object that renders in 3D objects using [Assimp](https://github.com/assimp/assimp), and textures using [stb_image](https://github.com/nothings/stb). These classes were created from following [learnopengl.com](https://learnopengl.com)'s Mesh tutorial.

- `GarageShaders/`

A library containing a `Shader` class, performing operations on shaders (i.e. Fragment and Vertex Shaders). These were also created from following [learnopengl.com](https://learnopengl.com)'s Mesh tutorial.

- `Demo/`

A project meant to demonstrate the capabilities / features of this project. This is where the movable camera can be found, and where most of the [GLFW](https://www.glfw.org/) and [GLEW](https://glew.sourceforge.net/) functions are called. 

## :books: Learning Sources :books:

The following sources are what I used to learn OpenGL:

- [Anton's OpenGL 4 Tutorials](https://www.amazon.ca/Antons-OpenGL-Tutorials-Anton-Gerdelan-ebook/dp/B00LAMQYF2) (C focused, lab-like assignments)
- [learnopengl.com](https://learnopengl.com) (C++ focused, step-by-step guides)

## :pencil: Project Status / DevLog :pencil:

- Looking light features to mesh objects to support 3 different light modes (point, spot, directional). The shaders exist, just need to write the shaders for the meshes and create a demo!
- Writing and setting up mesh objects can be a hassle to set up. Might need to invest some time in working on an Entity Component System.

## :rocket: Features to Work on Next :rocket:

The following are a list of features to implement in the feature

- Entity Component System
- Physics (with an external library like [Bullet Physics](https://github.com/bulletphysics/bullet3))
- Completing Advanced OpenGL and Lighting on [learnopengl.com](https://learnopengl.com/Advanced-OpenGL/Depth-testing)

## :video_camera: Project Playlist :video_camera:

You can find the project playlist here:

[<img alt="Project Playlist" width="640px" height="480px" src="https://github.com/megarage9000/openGLProjects/blob/main/thumbnails/thumbnail_1.png" />](https://www.youtube.com/playlist?list=PLoYQN9sSaKPZtNqR3CzW2sLVft5kNCWhi)

   
