# RenderTest

> The GL in OpenGL stands for "Good Luck" because you are going to need it.
> - Anonymous

Educational project to explore modern (4.6+) OpenGL and general rendering techniques.

Based on the following tutorials
* https://learnopengl.com
* http://www.opengl-tutorial.org
* https://open.gl
* http://ogldev.atspace.co.uk
* https://www.spieleprogrammierung.net/p/opengl-tutorial-liste.html
* https://www.tomdalling.com/blog/category/modern-opengl
* http://lazyfoo.net/tutorials/OpenGL
* https://antongerdelan.net/opengl
* http://www.mbsoftworks.sk/tutorials
* http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Table-of-Contents.html

## Requirements

The project uses
* Conan
* CMake
* LLVM (clang-format)
* Visual Stuctio 2019 Community Edition

Copy the pre-commit hook from doc/ to the .git/hooks directory for auto formatting of the source code using clang-format

## Building

Running cmake and the platform specific build command should be enough to build this project.

Example: Linux system, in-source build.
 
```
git clone <project-web-url> <project-dir>
cd <project-dir>
cmake .
make
```