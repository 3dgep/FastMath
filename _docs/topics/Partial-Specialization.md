# Partial Specialization

Partial template specialization allows customizing variable and class templates when some of the template arguments are specified.

## Partial Specialization of Function Templates

Although it is not possible to partially specialize function templates, we can achieve something similar by using function template overloading.
Let’s consider the `max` function template introduced in [Function Templates](Function-Templates.md). Suppose we want to provide an implementation for pointer types:

```c++
```
{src="FunctionTemplates.hpp" include-lines="53-57" collapsible="true" default-state="expanded" collapsed-title-line-number="2"}

This version of the function template is used whenever pointers are used as the arguments to the function as in the following example:

```c++
```
{src="FunctionTemplates.cpp" include-lines="5-8" collapsible="true" default-state="expanded"}

> Strictly speaking, this is not partial specialization because none of the template parameters are specialized.
> We’re just providing a specific implementation when the types exhibit specific characteristics.

## Partial Specialization of Class Templates

Unlike function templates, class templates can be partially specialized.
Consider the `Array` class template from [Class Templates](Class-Templates.md).
A special implementation can be created for pointer types:

```c++
```
{src="Array.hpp" include-lines="65-87" collapsible="true" default-state="expanded" collapsed-title-line-number="2"}

A class template can be partially specialized by specifying the template keyword followed by a list of template parameters surrounded by angle brackets, just as with the non-specialized class template.
The specialized template parameters are specified after the class name (`T*` and `N` in this case).

This implementation of the `Array` class template is used when `T` is a pointer type.
This may not seem like a very useful thing. However, now we have a class template that can provide all the functionality of the original `Array` class template, but instead of allocating a static array, it now works with arbitrary data allocated elsewhere.

```c++
```
{src="Array.cpp" include-lines="30-33" collapsible="true" default-state="expanded"}

Similar to a fully specialized class template, if one of the template parameters is fully defined, then it does not need to be listed in the template parameter list. However, it must be specified in the template argument list (after the class name):

```c++
```
{src="Array.hpp" include-lines="89-101" collapsible="true" default-state="expanded"}

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/partial_specialization">Partial Template Specialization</a>
        <a href="https://en.cppreference.com/w/cpp/language/template_specialization">Full Template Specialization</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>

