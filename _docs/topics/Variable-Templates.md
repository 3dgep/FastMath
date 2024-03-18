# Variable Templates

A variable template is used to define a family of variables that can be represented with different types.

_Variable templates_ were added to the C++ standard with C++14.
Variable templates allow you to define a family of variables or static data members of a class using template syntax.

```c++
```
{src="VariableTemplates.hpp" include-lines="1-2" collapsible="true" default-state="expanded"}

The variable template `PI` can now be used with varying levels of precision:

```c++
```
{src="VariableTemplates.cpp" include-lines="1-8,11" collapsible="true" default-state="expanded"}

Will print:

```Bash
3
3.1415927410125732421875
3.14159265358979311599796346854
```

Variable templates can also have both type and non-type template parameters:

```c++
```
{src="VariableTemplates.hpp" include-lines="4-5" collapsible="true" default-state="expanded"}

`T` is a type template parameter and `N` is a non-type template parameter of type `T`.

> It’s important to understand that a variable template does not define a type, but rather a value that is evaluated at compile-time.
{style="warning"}

```c++
```
{src="VariableTemplates.cpp" include-lines="13-14" collapsible="true" default-state="expanded"}

Similar to function templates, variable templates can also be specialized:

```c++
```
{src="VariableTemplates.hpp" include-lines="7-17" collapsible="true" default-state="expanded"}

The `Fib` variable template computes the Nth Fibonacci number at compile-time.
The following example can be used to print the 10th Fibonacci number to the console:

```c++
```
{src="VariableTemplates.cpp" include-lines="10" collapsible="true" default-state="expanded"}

This will print `55` to the console.

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/variable_template">Variable template</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>
