# Template Specialization

Template specialization is a technique to define a different implementation for a function or class template for a give set of template arguments.

Both function templates and class templates can be specialized for specific types.
When all template parameters are specialized, then it is called fully specialized.

## Function Template Specialization

Suppose we have the following function template definition:

```c++
```
{src="FunctionTemplates.hpp" include-lines="30-35" collapsible="true" default-state="expanded" collapsed-title-line-number="2"}

The function template can be specialized by declaring the function with an empty template parameter list (`template<>`) and specifying the specialized template arguments after the function name:

```c++
```
{src="FunctionTemplates.hpp" include-lines="37-42" collapsible="true" default-state="expanded" collapsed-title-line-number="2"}

> It is also possible to provide the same effect by using function overloading:
{style="note"}

```c++
```
{src="FunctionTemplates.hpp" include-lines="44-48" collapsible="true" default-state="expanded" collapsed-title-line-number="2"}

The compiler will use the specialized (or overloaded) version of the function template if all the substituted template arguments (either explicitly or implicitly) match the specialized version.

```c++
```
{src="FunctionTemplates.hpp" include-lines="50-51" collapsible="true" default-state="expanded"}

## Class Template Specialization

Similar to function templates, class templates can also be specialized.
If we take the `Array` class template from the [Class Templates](Class-Templates.md) topic, and we want to specialize it for 4-component floating-point values:

```c++
```
{src="Array.hpp" include-lines="32-63" collapsible="true" default-state="expanded"}

The specialized version of the `Array` class template allows you to provide a different implementation of the class depending on its template arguments.
In this case, we provide a specialization for `Array<float, 4>` that allows for some SSE optimizations to be made.

It is important to note that if you specialize a class template, you must also specialize all the member functions of that class.
This can be quite cumbersome for large classes, especially if you decide to refactor the generic class template, you must also update all specialized versions of the class.

Keep in mind that the compiler will only generate code for class template member functions that are used (unless the class is [explicitly defined](Explicit-Instantiation.md)).
That is, if you never call a specific member function of a specialized class template, then no code will be generated for that version of the member function.

If a specialized class template defines a member function that just doesn't make any sense for a certain specialized type, and you are sure that the member function is not being used anywhere in the codebase, then you can leave that function undefined in the specialized version of the class template.

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/template_specialization">Template Specialization</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>
