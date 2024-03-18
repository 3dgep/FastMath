#include "FunctionTemplates.hpp"

int main()
{
    double d = 3.0;
    int i = 5;

    auto k = max(&d, &i); // Uses double max(const double* a, const int* b)

    return 0;
}