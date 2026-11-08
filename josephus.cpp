#include <iostream>
using namespace std;

long long ostatnia_zabita(int n)
{
    long long najwieksza_potega_dwojki = 1;
    while ((najwieksza_potega_dwojki << 1) <= n)
        najwieksza_potega_dwojki <<= 1;
    return 2 * (n - najwieksza_potega_dwojki) + 1;
}

void flawiusz(long long n, long long k)
{
    if (k < 0)
    {
        k = n + k + 1; // np. -1 oznacza ostatnią zmarłą osobę
    }


    // Szybkie przypadki:
    if (k <= n / 2)
    {
        cout << k * 2 << endl;
        return;
    }

    if (k == n)
    {
        cout << ostatnia_zabita(n) << endl;
        return;
    }

    // Pełna symulacja tylko dla przypadków nieobsługiwanych wzorami:
    bool *osoby = new bool[n]; // dynamiczna tablica
    for (long long i = 0; i < n; i++)
        osoby[i] = true;

    long long zabici = 0;
    long long index = 0;
    long long licznik = 0;

    while (zabici < k)
    {
        if (osoby[index])
        {
            licznik++;
            if (licznik == 2)
            {
                osoby[index] = false;
                zabici++;
                licznik = 0;

                if (zabici == k)
                {
                    cout << index + 1 << endl; // numer osoby (1-based)
                    delete[] osoby;
                    return;
                }
            }
        }
        index = (index + 1) % n;
    }

    delete[] osoby;
}

int main()
{
    long long ilDanych;
    while (cin >> ilDanych)
    {
        for (long long i = 0; i < abs(ilDanych); i++)
        {
            long long n, k;
            cin >> n >> k;
            flawiusz(n, k);
        }
    }
    return 0;
}