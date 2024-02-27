# Template Specialization

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
