#include <iostream>

int main()
{
    std::cout << std::setprecision(30);
    std::cout << PI<int> << std::endl;
    std::cout << PI<float> << std::endl;
    std::cout << PI<double> << std::endl;

    std::cout << Fib<10> << std::endl;
}

integral_constant<int, 3> i;        // ERROR integral_constant<int, 3> is not a type.
auto i = integral_constant<int, 3>; // OK: i is an int with the value 3.