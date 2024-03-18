#include "Array.hpp"

Array<float, 3> Position;
Array<float, 3> Normal;
Array<float, 2> TexCoord;

Array<float, 2> add(const Array<float, 2>& a, const Array<float, 2>& b)
{
    Array<float, 2> c;

    c[0] = a[0] + b[0];
    c[1] = a[1] + b[1];

    return c;
}

...

Array<float, 3> Position1;
Array<float, 3> Position2;

auto Position3 = add(Position1, Position2); // Error: Array<float, 3> is not compatible with Array<float, 2>

template Array<float, 2>; // Explicit template instantiation definition.
template Array<float, 3>; // Explicit template instantiation definition.
template Array<float, 4>; // Explicit template instantiation definition.

int main()
{
    float p[16] = {};
    auto a = Array<float*, 16>(p);
    // a provides all the functionality of Array on arbitrary data.
    a[8] = 1.0f;
}
