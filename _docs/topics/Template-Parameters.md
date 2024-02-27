# Template Parameters

Before we get into the various types of templates that we can create in C++, let's first take a look at the different types
of parameters a template can have. 
First, let's define the distinction between a _template parameter_, and a _template argument_:

Template Parameter
: A placeholder for a variable in the template parameter list.

Template Argument
: A value that is used to instantiate a function template, a class template, or a variable template.

Perhaps you are already familiar with the difference between a _parameter_ and an _argument_.
If not, this might seem a bit abstract, so let's take a look at an example.

Suppose we have the following class template definition:

```c++
```
{src="Array.hpp" include-lines="1-7,28-30" collapsible="true" default-state="expanded" collapsed-title="Array.hpp"}

The `Array` class template can be _instantiated_ like this:

```c++
```
{src="Array.cpp" include-lines="3-5" collapsible="true" default-state="expanded" collapsed-title="Array.cpp"}

In this example, `T` and `N` are the template parameters and `float` is the _type_ template argument and `2` and `3` are the _non-type_ template arguments.
You can say that "_parameters_ are initialized with _arguments_".

> Template _parameters_ are the placeholders for _arguments_ and _parameters_ are initialized by _arguments_.
{style="note"}

Now that we understand the difference between parameters and arguments, let's take a closer look at the different types of parameters a template can have.
Each parameter in a template parameter list can be one of:

1. A type template parameter
2. A non-type template parameter
3. A template-template parameter

The `Array` class template demonstrates the use of both type (`T`) and non-type (`N`) template parameters.
In the following sections, all three parameter types are explained in more detail.

## Type Template Parameter

The most common template parameter is a _type template parameter_.
A type template parameter starts with either `typename` or `class` and (optionally) followed by the parameter name.

> `typename` and `class` are synonyms of each other, and there is no difference between these keywords when used in a template parameter list.
{style="note"}

The name of a template parameter has the same naming rules as an identifier used in a [typedef][typedef] of a [type alias][type_alias].

A type template parameter may define a default argument. If a type template parameter provides a default value, it must appear at the end of the parameter list.

A type template parameter may be a _parameter pack_.
A parameter pack starts with `typename...` (or `class...`) and is used to list an unbounded number of type template parameters.
Template parameter packs are discussed in more detail in the section about [parameter packs](#template-parameter-pack).

The following examples demonstrate the use of type template parameters.

```c++
```
{src="TemplateParameters.hpp" include-lines="1-14" collapsible="true" default-state="expanded"}

## Non-type Template Parameter

Non-type template parameters can be used to specify a _value_ rather than a _type_ in the template parameter list.

Non-type template parameters can be:

1. An integral type (`bool`, `char`, `int`, `size_t` and unsigned variants of those types)
2. <shortcut>C++20</shortcut> A floating-point type (`float`, `double`)
3. An enumeration type
4. An lvalue reference type (a reference to an existing object or function)
5. A pointer type (a pointer to an existing object or function)
6. A pointer to a member type (a pointer to a member object or member function of a class)
7. [std::nullptr_t](https://en.cppreference.com/w/cpp/types/nullptr_t)
8. <shortcut>C++20</shortcut> A literal class type

Don't worry too much about the different ways a non-type template parameter can be specified. 
We will only be concerned with integral types in this series.

Similar to type template parameters, the name of the template parameter is optional and non-type template parameters may also specify default arguments.

> Non-type template parameters must be constant values that are evaluated at compile-time.
{style="note"}

The following code snippet shows examples of non-type template parameters:

```c++
```
{src="TemplateParameters.hpp" include-lines="16-44" collapsible="true" default-state="expanded"}

## Template Template Parameter

Templates can also be used as template parameters. 
Since template template parameters will not be used in this series, I will only briefly show an examples of template template parameters.

```c++
```
{src="TemplateParameters.hpp" include-lines="46-53" collapsible="true" default-state="expanded"}

> Prior to C++17, template template parameters could only be declared using the `class` keyword (as shown in the first two examples in the code snippet).
> Since C++17, both `class` and `typename` can be used to declare a template template parameter.
{style="note"}

## Template Parameter Pack

A _template parameter pack_ is a placeholder for zero or more template parameters. 
A template parameter pack can be applied to type, non-type, and template template parameters, but the parameter types cannot be mixed in a single parameter pack.

A few examples of template parameter packs:

```c++
```
{src="TemplateParameters.hpp" include-lines="55-65" collapsible="true" default-state="expanded"}

A pack followed by an ellipsis expands the pack. 
A pack is expanded by replacing the pack with a comma-separated list of the template arguments in the pack.

For example, if a function template is defined with a parameter pack:

```c++
```
{src="TemplateParameters.hpp" include-lines="67-71" collapsible="true" default-state="expanded"}

Then invoking the function:

```c++
```
{src="TemplateParameters.hpp" include-lines="73"}

Will result in the following expansion:

```c++
```
{src="TemplateParameters.hpp" include-lines="75-78" collapsible="true" default-state="expanded"}

> A template with at least one parameter pack is called a _variadic template_.
{style="note"}


<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/templates">Templates</a>
        <a href="https://en.cppreference.com/w/cpp/language/template_parameters">Template parameters and template arguments</a>
        <a href="https://en.cppreference.com/w/cpp/language/parameter_pack">Parameter pack</a>
        <a href="https://en.cppreference.com/w/cpp/language/type_alias">Type alias, alias template</a>
        <a href="https://en.cppreference.com/w/cpp/language/typedef">typedef specifier</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>

[typedef]: https://en.cppreference.com/w/cpp/language/typedef
[type_alias]: https://en.cppreference.com/w/cpp/language/type_alias