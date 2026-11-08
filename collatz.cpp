#include <iostream>
#include <array>
#include <cstdint>
using namespace std;

int ciagCollatza(uint64_t n)
{
    array<int64_t, 700> pomocniczy;
    int len = 0;

    while (n != 1)
    {
        int64_t x = -static_cast<int64_t>(n);
        int i = 0;
        while (i < len && pomocniczy[i] < x)
            ++i;
        if (i == len)
            pomocniczy[len++] = x;
        else
            pomocniczy[i] = x;

        n = (n & 1) ? 3 * n + 1 : n >> 1; // szybsze niż if/else
    }

    // Dodaj -1
    int64_t x = -1;
    int i = 0;
    while (i < len && pomocniczy[i] < x)
        ++i;
    if (i == len)
        pomocniczy[len++] = x;
    else
        pomocniczy[i] = x;

    return len;
}
int main()
{
    long long n;
    while (cin >> n)
    {
        cout << ciagCollatza(n) << endl;
    }
    return 0;
}