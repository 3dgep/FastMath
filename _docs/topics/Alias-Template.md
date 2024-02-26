# Alias Template

Templates can be aliased using the `using` keyword:

```c++
```
{src="AliasTemplates.hpp" include-lines="1-6" collapsible="true" default-state="expanded"}

`bool_constant` is defined as an alias template of the `integral_constant` variable template where `T` is bool.
The value `v` remains open as a non-type template parameter.