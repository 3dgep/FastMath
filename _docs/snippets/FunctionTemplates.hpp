template<typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

int m = max<int>(3, 5); // Explicit type.
int n = max(3, 5);      // Implicit type deduction.

double x = max(3, 5.0); // Cannot deduce template arguments.

double x = max<double>(3, 5.0); // 3 will be cast to double.

int x = max(3, static_cast<int>(5.0)); // Explicitly cast 5.0 to int.

template<typename T, typename U>
T max(T a, U b)
{
    return a > b ? a : b;
}

template<typename T, typename U>
auto max(T a, U b) -> decltype(a > b ? a : b)
{
    return a > b ? a : b;
}

auto x = max(3.0, 5); // Automatically deduce the return type.

// Primary template.
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b)
{
    return a + b;
}

// Specialized function template.
template<>
double add<double, double>(double a, double b)
{
    return a + b;
}

// Function overloading.
double add(double a, double b)
{
    return a + b;
}

float a = add(3.0f, 4.0f); // Uses primary function template.
double b = add(3.0, 4.0);  // Uses specialized version for doubles.

template<typename T, typename U>
auto max(const T* a, const U* b) -> decltype(*a > *b ? *a : *b)
{
    return *a > *b ? *a : *b;
}
