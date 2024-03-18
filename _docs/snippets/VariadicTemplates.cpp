#include "VariadicTemplates.hpp"

int main()
{
    int i = 3;
    float f = 4.0f;
    double d = 6.0;

    auto o = make_unique<Object>(i, f, &i, d);
}