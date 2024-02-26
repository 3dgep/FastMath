# FastMath

The _FastMath_ repository is intended to be used as a learning tool for beginning C++ game programmers. 
The primary object is to teach the reader how to create a template math library in C++.
Several topics are covered in these technical articles including:

1. C++ Templates
2. Vectors
3. Matrices
4. Quaternions
5. Transforms

Vectors and matrices are arguably the most common mathematical primitives used in games, especially in graphics programming.
By following these articles, you will build your own C++ math template library that you can use in your own game projects.

The series starts with an introduction to C++ template programming.
With a strong foundation in C++ templates, you will build a vector class template that will be the basis of the matrix class template.
With the vectors and matrices, you will also build a quaternion class template.

> Quaternions are commonly used to represent rotations in 3-dimensional space.
> Quaternions have some interesting properties that make them beneficial to using matrices for representing rotations. 

The final class template that we will build in this series is the `Transform` class template.
It is sometimes useful to represent translation, rotation, and scale as a _transform_.
If you've used [Unity][unity] before, then you are probably already familiar with the [`Transform`][transform] class that every [`GameObject`][gameobject] has.
If you're not familiar with Unity's [`Transform`][transform] class, the `Transform` class described in this article is used to represent the position, rotation, and scale of an object in the scene.

By the end of this series, you will have a reusable C++ template math library, and you will have a greater understanding of how to implement vectors, matrices, and quaternions in C++.

[unity]: https://unity.com/
[transform]: https://docs.unity3d.com/ScriptReference/Transform.html
[gameobject]: https://docs.unity3d.com/ScriptReference/GameObject.html