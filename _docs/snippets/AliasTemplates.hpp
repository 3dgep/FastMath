template<typename T, T v>
constexpr T integral_constant = v;

// Create an alias of the integral_constant for bool.
template<bool v>
using bool_constant = integral_constant<bool, v>;