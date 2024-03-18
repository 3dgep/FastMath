# FastMath Library

The `FastMath` library is a C++ template math library that implements vectors, matrices, and quaternions.

After reading the section on [C++ Templates](C-Templates.md), you should have a good foundation for template programming in C++.

In this section, we will go into the details of building the C++ math template library.
This section covers the following topics:

1. Vectors
2. Matrices
3. Quaternions
4. Transform

## Conventions

Throughout the following sections, I will use several conventions to represent the different types of mathematical primitives.
The following table describes these conventions:

| Type     | Notation          | Examples                      |
|----------|-------------------|-------------------------------|
| Scalars  | lower-case italic | _a_, _b_, _\theta_, _\lambda_ |
| Vectors  | lower-case bold   | **x**, **y**, **z**           |
| Matrices | upper-case bold   | **R**, **S**, **T**, **M**    |

## Style Guide

The FastMath library described in this article follows a specific style guide and coding conventions.
The <tooltip term="rule-of-thumb">rule-of-thumb</tooltip> is to favor <tooltip term="succinct">succinct</tooltip> over <tooltip term="verbose">verbose</tooltip>.
For this reason, I tend to prefer a coding style that reduces the length of class and variable names, without sacrificing clarity.
For example, I prefer to use [camelCase][camel_case] (also known as _lower camel case_) or [PascalCase][camel_case] (also known as _upper camel case_) for variables and class names instead of [snake_case][snake_case] which is commonly used by the [Standard Template Library](https://isocpp.org/).

### Clean Interfaces

The interface of a class should not contain more code than necessary.
For this reason, I prefer to only _declare_ the member functions of a class in the class declaration, and _define_ the member functions outside the class.

### Minimize Includes


### Type Names

Class names use _PascalCase_ 

<seealso>
    <category ref="external">
        <a href="https://isocpp.org/wiki/faq/coding-standards">C++ Coding Standards</a>
    </category>
    <category ref="reading">
        <a href="https://www.google.nl/books/edition/C++_Coding_Standards/mmjVIC6WolgC">C++ Coding Standards, 101 Rules, Guidelines, and Best Practices</a>
    </category>
</seealso>


[camel_case]: https://en.wikipedia.org/wiki/Camel_case
[snake_case]: https://en.wikipedia.org/wiki/Snake_case