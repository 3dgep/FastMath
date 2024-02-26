template<typename T>
constexpr T PI = T(3.1415926535897932384626433832795L);

template<typename T, T N>
constexpr T integral_constant = N;

// Primary template.
template<size_t N>
constexpr size_t Fib = Fib<N-1> + Fib<N-2>;

// Specialization when N == 0.
template<>
constexpr size_t Fib<0> = 0;

// Specialization when N == 1.
template<>
constexpr size_t Fib<1> = 1;