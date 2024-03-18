# Variadic Templates

Variadic templates are function templates or class templates that can accept an unbounded number of template arguments.

For example, suppose we want a function that creates a [std::unique_ptr][unique_ptr] from an arbitrary type:

```c++
```
{src="VariadicTemplates.hpp" include-lines="1-5" collapsible="true" default-state="expanded" collapsed-title-line-number="2"}

> For some reason, [std::make_shared][make_shared] was introduced in C++11 but [std::make_unique][make_unique] wasn't introduced until C++14.
> This example provides a possible implementation of [std::make_unique][make_unique] for C++11 compilers.
{style="note"}

There are a few things to note here:

1. The template parameter list contains a _template parameter pack_ in the form of `typename... Args`
2. An arbitrary number of arguments are passed to the function in the form of `Args&&...`. Not to be mistaken by an _r-value reference_, this is called a [forwarding reference][forwarding_references] which preserves the value category of the function arguments when used in conjunction with [std::forward][forward]
3. The arguments are unpacked by performing a _pack expansion_ which replaces the parameter pack by a comma-separated list of the arguments using the pattern immediately preceding the `...` (ellipsis)

For example, suppose we have the following class:

```c++
```
{src="VariadicTemplates.hpp" include-lines="7-22" collapsible="true" default-state="expanded"}

And if the `make_unique` function template was invoked with:

```c++
```
{src="VariadicTemplates.cpp" include-lines="5-9" collapsible="true" default-state="expanded"}

Then the `make_unique` function would generate something like this:

```c++
```
{src="VariadicTemplates.hpp" include-lines="24-27" collapsible="true" default-state="expanded"}

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/memory/unique_ptr">std::unique_ptr</a>
        <a href="https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique">std::make_unique</a>
        <a href="https://en.cppreference.com/w/cpp/utility/forward">std::forward</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>


[unique_ptr]: https://en.cppreference.com/w/cpp/memory/unique_ptr
[make_unique]: https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
[make_shared]: https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
[forwarding_references]: https://en.cppreference.com/w/cpp/language/reference#Forwarding_references
[forward]: https://en.cppreference.com/w/cpp/utility/forward