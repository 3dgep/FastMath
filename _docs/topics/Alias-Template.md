# Alias Template

An alias template is used to define another name for a class or variable template with zero or more specified template arguments.

Templates can be aliased using the `using` keyword:

```c++
```
{src="AliasTemplates.hpp" include-lines="1-6" collapsible="true" default-state="expanded"}

`bool_constant` is defined as an alias template of the `integral_constant` variable template where `T` is bool.
The value `v` remains open as a non-type template parameter.

<seealso>
    <category ref="cppreference">
        <a href="https://en.cppreference.com/w/cpp/language/type_alias">Alias Template</a>
    </category>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
</seealso>
