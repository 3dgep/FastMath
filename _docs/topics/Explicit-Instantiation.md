# Explicit Instantiation

Declaring a class template does not actually cause any code to be generated unless the class template is _instantiated_ (either implicitly or explicitly).
A class template is instantiated when template arguments are provided which will instruct the compiler to instantiate the class template with the specified template arguments.

An explicit template instantiation forces the compiler to create a definition of your class template with specific template arguments.
This has multiple advantages:

1. The class template is compiled. If there are any syntax errors (or warnings), you're compiler will let you know.
2. Reduced compilation times if the same set of template arguments are used in multiple compilation units.

If you want to take advantage of explicit template instantiation in your template library, you must consider two things:

1. Explicit instantiation _definition_
2. Explicit instantiation _declaration_

## Explicit Instantiation Definition

To explain explicit template instantiation definition, let's use the `Array` example from the previous sections.
Here is the (abridged) code again for clarity:

```c++
```
{src="Array.hpp" include-lines="1-7,27-30" collapsible="true" default-state="expanded"}

This is the code that appears in the <path>Array.hpp</path> header file for the `Array` class template.
To _define_ an explicit template instantiation for the class template, we must provide the template arguments for the class template.
The explicit template definition must only appear once in the entire program, so it should not be placed in the header file for your class template:

```c++
```
{src="Array.cpp" include-lines="1,23-25" collapsible="true" default-state="expanded" collapsed-title="Array.cpp"}

An explicit template instantiation definition must only appear in a single compilation unit in the entire program.
This is usually accomplished by placing the explicit template instantiation definition in a source file (<path>.cpp</path>) that is only compiled once for the entire program.

> Multiple _definitions_ of the same explicit template instantiation in the same program is a violation of the [One Definition Rule (ODR)][ODR] and likely cause linker errors.
{style="warning"}

## Explicit Instantiation Declaration

An _explicit instantiation declaration_ is used to let the compiler know that there is a matching _definition_ somewhere else in the program.
The declaration looks very similar to the definition, except with the `extern` keyword prepended to the declaration.

```c++
```
{src="Array.hpp" include-lines="32-33" collapsible="true" default-state="expanded"}

Unlike the definition, the declaration can appear as many times as necessary in any number of compilation units in your entire program.
When the compiler sees an explicit instantiation declaration, and you declare a variable using the same template arguments, it will skip the implicit instantiation step and use the code that was generated from the definition instead.

> An explicit template _declaration_ without a matching _definition_ will result in an "unresolved external symbol" linker error.
> Make sure to link the source file that contains the matching explicit template _definitions_.
{style="warning"}

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/templates">Class Template</a>
        <a href="https://en.cppreference.com/w/cpp/language/class_template">Definitions and ODR</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>

[ODR]: https://en.cppreference.com/w/cpp/language/definition
[class_template]: https://en.cppreference.com/w/cpp/language/class_template