#pragma once

inline int abc(const int a, const int b, const int c)
{

    if (a < 0 && b < 0 && c < 0)
    {
        throw 1;  // NOLINT(hicpp-exception-baseclass)
    }

    if (a == 0 && b == 0 && c == 0)
    {
        throw 2;  // NOLINT(hicpp-exception-baseclass)
    }

    if (a < 0 || b < 0 || c < 0)
    {
        throw 0;  // NOLINT(hicpp-exception-baseclass)
    }

    return a + b + c;
}
