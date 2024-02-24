#pragma once
#include <concepts>
#include <limits>

/// <summary>
/// A concept that checks if a type (`From`) is convertible to 
/// another type (`To`).
/// </summary>
/// <see cref="ls::Math::Matrix" />
template<typename From, typename To>
concept ConvertibleTo = std::convertible_to<From, To>;

/// <summary>
///	A concept that constrains types to floating-point types.
/// </summary>
///	<remarks>
///	Valid floating-point types are:
///	 * float
///	 * double
///  * long double
///	</remarks>
template<typename T>
concept FloatingPoint = std::floating_point<T>;

/// <summary>
/// A concept that constrains types to the integral types.
///	</summary>
template<typename T>
concept Integral = std::integral<T>;

/// <summary>
///	A concept to constrain types to arithmetic types.
/// <summary>
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

/// <summary>
///	A concept to constrain types that define infinity.
/// <summary>
template<typename T>
concept HasInfinity = std::numeric_limits<T>::has_infinity;
