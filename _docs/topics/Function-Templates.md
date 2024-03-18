# Function Templates

Function templates provide a mechanism to define a family of functions that operates on different types.

Function templates look like ordinary functions but start with the `template` keyword followed by a list of (one or more) template parameters surrounded by angle brackets.

```c++
```
{src="FunctionTemplates.hpp" include-lines="1-5" collapsible="true" default-state="expanded"}

The `max` function in the example code accepts a single template parameter `T`.
The `max` function template defines a _family_ of functions that can take different types.
The type is defined when the function is _instantiated_ either by explicitly specifying the type of by allowing the compiler to deduce the type:

```c++
```
{src="FunctionTemplates.hpp" include-lines="7-8" collapsible="true" default-state="expanded"}

On the first line, `int` is explicitly provided as the template argument.
On the second line, the template argument is not specified, but the compiler automatically deduces it as `int` because `3` and `5` are both deduced as `int`. In both cases, the same function definition is instantiated.

Implicit template type deduction does not work if you want to mix types as in the following case:

```c++
```
{src="FunctionTemplates.hpp" include-lines="10"}

In this case, the `max` function template is invoked with `3` (which is an `int`) and `5.0` (which is a `double`) and the compiler does not know to implicitly deduce the template argument type. 
In this case, the compiler will generate an error.
There are a few ways this can be resolved:

1. Use an explicit template argument
2. Cast all function arguments to the same type
3. Multiple template parameters

Explicitly specifying the template arguments ensures that all the parameters are cast to the correct type through implicit casting:

```c++
```
{src="FunctionTemplates.hpp" include-lines="12"}

In this example, `3` is implicitly cast to `double`. 
In this case, the compiler may not issue a warning since this type of cast does not cause any loss of precision.
However, if a narrowing conversion occurs, the compiler will likely generate a warning.
To avoid the warning, an explicit cast can be used.

```c++
```
{src="FunctionTemplates.hpp" include-lines="14"}

In this example, an explicit cast is used to convert `5.0` from a `double` to an `int`.
The compiler no longer generates a warning and `T` is implicitly deduced to `int`.

The other solution to this problem is to allow `a` and `b` to be different types:

```c++
```
{src="FunctionTemplates.hpp" include-lines="16-20" collapsible="true" default-state="expanded"}

Now `a` and `b` can be different types, and we can call the function template with mixed types without the compiler issuing any warnings... right? 
What about the return type?
If `T` is a narrower type than `U`, then the compiler will have to perform a narrowing conversion again and likely issue a warning when this happens.
So what should the return type be? Is it possible to let the compiler decide?

Since the compiler will do anything to prevent data loss, it will try to convert all arguments to the largest (widest) type before performing the comparison, and the return type will be the widest type.
We can use the _auto return type deduction_, [trailing return type][function], and the [`decltype`][decltype] specifier to automatically determine the safest type to use for the return value of the function template:

```c++
```
{src="FunctionTemplates.hpp" include-lines="22-26" collapsible="true" default-state="expanded"}

> In C++14 and later, the trailing return type can be omitted.
{style="note"}

> This version of the `max` function template may still generate a warning about returning a reference to a temporary, but we can use type traits to avoid this. 
> Type traits are not discussed in this series, so I won’t complicate this example more than necessary for now.
{style="warning"}

Using this version of the function template, any type can be used for `a` and `b` and the return value is the widest type of `a` or `b`. For example:

```c++
```
{src="FunctionTemplates.hpp" include-lines="28"}

`x` is automatically dedcued to `double` because comparing `3.0` (as a `double`) and `5` (as an `int`) results in a conversion to `double` and the `max` function returns `double`.

> There is also a solution to determine the return type using [`std::common_type`][common_type] but requires knowledge of type traits which are not discussed here.
{style="note"}

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/function">Function declaration</a>
        <a href="https://en.cppreference.com/w/cpp/types/common_type">std::common_type</a>
        <a href="https://en.cppreference.com/w/cpp/language/decltype">decltype specifier</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>

[function]: https://en.cppreference.com/w/cpp/language/function
[decltype]: https://en.cppreference.com/w/cpp/language/decltype
[common_type]: https://en.cppreference.com/w/cpp/types/common_type