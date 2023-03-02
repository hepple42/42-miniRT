# 42-minishell

<img width="1498" alt="42-logo" src="https://user-images.githubusercontent.com/56789534/173826141-045ce31b-b8be-4065-b711-4e385cb72ef6.png">

This repository contains one of my projects of the core curriculum at [42 Heilbronn], done together with [tjensen42].

The project miniRT is an introduction to the beautiful world of raytracing. 
As with all C projects at 42 Heilbronn, the code has to be written according to the 42 Norm (maximum 25 lines per function, no for loops, a certain set of allowed functions, ...).

## Description

The task in this project is to implement a raytracing algorithm to render computer-generated images, using the 42 graphics library [MLX42].
The requirements include:

- 3 geometric objects: plane, sphere, cylinder
- variable object size
- rotation and translation of objects
- lighting system: diffuse light, ambient light
- configuration of scenes using a scene file with all relevant information

The bonus part consists of:

- specular reflections
- checkerboard coloring
- multiple light sources
- another 3D object
- textures

## Approach

Being a physicist, this was definitely my favorite project at 42 so far.
This combination of fundamental physics and math one one side and the implementation in code on the other was really interesting to me.

Working on this project, we noticed more and more interesting optical effects in everyday life and were constantly thinking about possible implementation in our raytracer.
Once the basic principle was implemented, it was fun to add more and more objects and functionalities.

As a result of this enthusiasm about the topic, we implemented a lot more features than the project required.
As a general reference, we used the excellent [Ray Tracing in One Weekend] series of books by Peter Shirley, which offers a really detailed step-by-step guide for implementing a raytracer based on path tracing in C++.

Our general approach for rendering is to generate multiple rays per image pixel, and to trace their complete path through the scene until they hit a source of light.
Some surfaces in a scene cause scattering to a random direction, so we may get different results for each ray. Averaging over all the rays corresponding to one pixel, we obtain the final picture.
Thus, increasing the number of rays per pixel results in better and better images.

## Features

The following features are implemented in our raytracer:

- 7 types of objects: sphere, plane, rectangle, cuboid, disc, tube, cylinder
- 3 types of light sources: sphere, rectangle, disc
- 3 types of surface interactions: scattering, reflection, refraction (mixtures possible)
- multithreading-based live rendering for improving image quality over time 
- 3D camera movement and rotation
- 2 different sampling techniques for diffuse scattering
- textures and checkerboard coloring
- ambient lighting

## How to Use

The only supported and tested operating systems are __macOS__ and __Ubuntu 20.04__.

For Ubuntu, it is necessary to install the GLFW library first:
```
sudo apt-get update && \
sudo apt-get install libglfw3 && \
sudo apt-get install libglfw3-dev
```

Compile and run miniRT in 3 simple steps:

Clone this repository:
```
git clone --depth 1 https://github.com/hepple42/42-miniRT miniRT
```
Change to the cloned directory and build the project:
```
cd miniRT && make
```
Run the program using our scene file template:
```
./miniRT scenes/template.rt
```
Alternatively, specify a custom scene file:
```
./miniRT [scene_file_path]
```

## Scene File

As an example and an overview of features and syntax, check our [template] scene file.

<table>
<tr><th>General</th><th>Lights</th><th>Textures</th><th>Objects</th></tr>
<tr><td>

| ID | Description |
| :-- | :-- |
| `R` | Resolution |
| `S` | Sampling |
| `B` | Background |
| `A` | Ambient Light |
| `C` | Camera |

</td><td>

| ID | Description |
| :-- | :-- |
| `ls` | Light Sphere |
| `lr` | Light Rectangle |
| `ld` | Light Disc |
  
</td><td>
  
| ID | Description |
| :-- | :-- |
| `tx` | Texture |
  
</td><td>
  
| ID | Description |
| :-- | :-- |
| `pl` | Plane |
| `sp` | Sphere |
| `cy` | Cylinder |
| `tb` | Tube |
| `di` | Disc |
| `rt` | Rectangle |
| `cu` | Cuboid |

</td></tr> </table>

## Camera Movement and Rotation

Note that the image has to be rerendered after every camera adjustment.

<table>
<tr><th>Movement</th><th>Rotation</th></tr>
<tr><td>

| Key | Action |
| :-- | :-- |
| `W` | Move Forward |
| `S` | Move Backward |
| `A` | Move Left |
| `D` | Move Right |
| `E` | Move Up |
| `Q` | Move Down |

</td><td>

| Key | Action |
| :-- | :-- |
| `⇧` | Rotate Up |
| `⇩` | Rotate Down |
| `⇦` | Rotate Left |
| `⇨` | Rotate Right |

</td></tr> </table>

## Samples

<img width="2672" alt="Screen Shot 2022-05-27 at 12 25 43 PM" src="https://user-images.githubusercontent.com/56789534/180815692-0fa071c2-1b2b-44e5-a3d9-6baf9aab7e5e.png">
<img width="2628" alt="777" src="https://user-images.githubusercontent.com/56789534/180815726-fefe9787-4059-431f-a05d-43e2bc5220fd.png">
<img width="2628" alt="135" src="https://user-images.githubusercontent.com/56789534/180815864-a63f059a-2897-4294-9042-de597fa87d11.png">
<img width="2560" alt="6000" src="https://user-images.githubusercontent.com/56789534/180816221-ed3e7391-d8e4-4e61-a4cb-fe73ed5923d1.png">
<img width="2112" alt="template" src="https://user-images.githubusercontent.com/56789534/180817985-70f5c204-60c4-46e7-a9ce-8d267b5df52b.png">
<img width="1068" alt="Screen Shot 2022-05-31 at 10 50 14 AM" src="https://user-images.githubusercontent.com/56789534/180815911-c11b4893-e891-4706-a0c9-bbb166b63625.png">
<img width="1068" alt="Screen Shot 2022-06-07 at 2 56 40 PM" src="https://user-images.githubusercontent.com/56789534/180815915-97fe7f6c-0978-4ed8-a975-8df527e2c391.png">
<img width="1568" alt="600" src="https://user-images.githubusercontent.com/56789534/180814525-86fafb66-9f24-4098-beb8-28eb454f0f78.png">
<img width="1068" alt="random-42-color" src="https://user-images.githubusercontent.com/56789534/180814553-7e658d79-da34-49af-8438-79086d8e3ac8.png">
<img width="1112" alt="rgb-color" src="https://user-images.githubusercontent.com/56789534/180814564-d6d0e465-bf73-41b9-bceb-6b9f1f507b79.png">


[42 Heilbronn]: https://www.42heilbronn.de/learncoderepeat
[tjensen42]: https://github.com/tjensen42

[MLX42]: https://github.com/codam-coding-college/MLX42

[Ray Tracing in One Weekend]: https://raytracing.github.io/

[template]: https://github.com/hepple42/42-miniRT/blob/main/scenes/template.rt
