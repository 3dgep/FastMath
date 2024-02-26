# Class Templates

Similar to [Function Templates](Function-Templates.md), classes can also be parameterized with one or more template parameters.
The most common use cases for class templates are containers for other types.
If you have used any of the container types in the Standard Template Library (STL) (such as [`std::vector`][vector], [`std::map`][map], or [`std::array`][array]), then you have already used class templates.
In this chapter, I describe how to create class templates.

Consider the `Array` class template from the previous chapter.
Here it is again for clarity:

```c++
```
{src="Array.hpp" include-lines="1-30" collapsible="true" default-state="expanded"}

> A class template that doesn't specialization any template parameters is called a _primary template_.
{style="note"}

The `Array` class template demonstrates the use of two types of template parameters:

1. Type template parameters (denoted with `typename` or `class`)
2. Non-type template parameters (denoted with an integral type such as `size_t`)

The `Array` class template defines a simple container for a static (fixed-size) array similar to the [`std::array`][array] implementation from the Standard Template Library.

Inside the `Array` class template, `T` can be used wherever a type is expected (such as the declaration of the `m_Data` member variable or the return value of a member function) and `N` can be used wherever the number of elements is required (such as in the `assert`'s in the index operator member functions).

A class template is instantiated when a variable that uses the class is defined:

```c++
```
{src="Array.cpp" include-lines="3,5" collapsible="true" default-state="expanded"}

Here, `Array<float, 3>` represents the _type_ of the `Position` variable and `Array<float, 2>` is the type of the `TexCoord` variable.
Although both types are instantiated from the same class template, they are in no way related. 
You cannot use `Array<float, 3>` where an `Array<float, 2>` is expected.
For example, the following code will not compile:

```c++
```
{src="Array.cpp" include-lines="7-22" collapsible="true" default-state="expanded"}

Although this is a pretty contrived example, it demonstrates that different combinations of template arguments create different (unrelated) types.

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/container/vector">std::vector</a>
        <a href="https://en.cppreference.com/w/cpp/container/map">std::map</a>
        <a href="https://en.cppreference.com/w/cpp/container/array">std::array</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>

[vector]: https://en.cppreference.com/w/cpp/container/vector
[map]: https://en.cppreference.com/w/cpp/container/map
[array]: https://en.cppreference.com/w/cpp/container/array