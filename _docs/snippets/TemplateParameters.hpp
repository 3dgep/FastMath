// typename introduces a type template parameter.
template<typename T> class Array { ... };

// class also introduces a type template parameter.
template<class T> struct MyStruct { ... };

// A type template parameter can specify a default value.
template<typename T = void> struct MyStruct { ... };

// The template parameter name is optional.
template<typename> struct Tag { ... };

// A type template parameter pack.
template<typename... Ts> class Tuple { ... };

// Integral non-type template parameter.
template<int C> struct Integral {};

// Another Integral non-type template parameter.
template<bool B> struct Boolean {};

// Enum non-type template parameter.
template<MyEnum E> struct Enumeration {};

// lvalue reference can also be used as a non-type template parameter.
template<const int& C> struct NumRef {};

// lvalue reference to an object is also allowed.
template<const std::string& S> struct StrRef {};

// Pointer to function.
template<void(*Func)()> struct Functor {};

// Pointer to member object or member function.
template<typename T, void(T::*Func)()> struct MemberFunc {};

// std::nullptr_t is also allowed as a non-type template parameter.
template<std::nullptr_t = nullptr> struct NullPointer {};

// Floating-point types are allowed in C++20
template<double N> struct FloatingPoint {};

// Literal class types are allowed in C++20.
template<MyClass C> struct Class {};

// C is a template class that takes a single type template parameter.
template<template<typename T> class C> struct TemplateClass {};

// C is a template class that takes a type and non-type template parameter.
template<template<typename T, size_t N> class C> struct ArrayClass {};

// keyword typename is allowed in C++17.
template<template<typename T> typename C> struct TemplateTemplateClass {};

// Function template with a parameter pack.
template<typename... Args> void func(Args... args);

// Type template parameter pack.
template<typename... Args> struct TypeList {};

// Non-type template parameter pack.
template<size_t... Ns> struct IntegralList {};

// Template template parameter pack.
template<template<typename T> class... Ts> struct TemplateList {};

template<typename... Args>
void func(Args... args)
{
    std::tuple<Args...> values(args...);
}

func(4, 3.0, 5.0f);

void func(int arg1, double arg2, float arg3)
{
    std::tuple<int, double, float> values(arg1, arg2, arg3);
}