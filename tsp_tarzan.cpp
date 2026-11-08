#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
#include <set>
using namespace std;

const double INF = 1e18;

// Funkcja do obliczenia odległości między dwoma punktami
double odlegloscAB(pair<int, int> A, pair<int, int> B)
{
    int dx = A.first - B.first;
    int dy = A.second - B.second;
    double d2 = dx * dx + dy * dy;

    if (d2 < 1000000.0)
    {
        return sqrt(d2);
    }
    if (A.second == B.second)
    {
        return abs(dx);
    }
    return abs(dy) + abs(A.first) + abs(B.first);
}

// Funkcja do rozwiązania problemu TSP z powrotem do punktu startu
double najkrotszaDroga(int ileWiosek, vector<pair<int, int>> &wioski)
{
    // Usuwanie zduplikowanych wiosek
    set<pair<int, int>> uniqueWioski(wioski.begin(), wioski.end());
    wioski.assign(uniqueWioski.begin(), uniqueWioski.end());
    ileWiosek = wioski.size();

    vector<vector<double>> macierzOdleglosci(ileWiosek, vector<double>(ileWiosek));

    // Obliczanie macierzy odległości
    for (int i = 0; i < ileWiosek; ++i)
    {
        for (int j = 0; j < ileWiosek; ++j)
        {
            macierzOdleglosci[i][j] = odlegloscAB(wioski[i], wioski[j]);
        }
    }

    // minDroga[mask][i] = minimalna droga kończąca się w i z odwiedzonymi wioskami mask
    vector<vector<double>> minDroga(1 << ileWiosek, vector<double>(ileWiosek, INF));

    // Zakładamy, że zaczynamy zawsze od wioski 0
    minDroga[1][0] = 0; // Odległość z wioski 0 do samej siebie to 0

    // DP Held-Karp
    for (int odwiedzoneWioski = 1; odwiedzoneWioski < (1 << ileWiosek); ++odwiedzoneWioski)
    {
        for (int u = 0; u < ileWiosek; ++u)
        {
            if (!(odwiedzoneWioski & (1 << u)))
                continue; // u nie jest w zbiorze
            for (int v = 0; v < ileWiosek; ++v)
            {
                if (odwiedzoneWioski & (1 << v))
                    continue; // v już odwiedzone
                int noweOdwiedzoneWioski = odwiedzoneWioski | (1 << v);
                minDroga[noweOdwiedzoneWioski][v] = min(minDroga[noweOdwiedzoneWioski][v], minDroga[odwiedzoneWioski][u] + macierzOdleglosci[u][v]);
            }
        }
    }

    // Szukanie najlepszego cyklu (wracamy do wioski 0)
    double najkrotszyDystans = INF;
    for (int i = 1; i < ileWiosek; ++i) // Startujemy od 1, bo 0 już odwiedziliśmy
    {
        najkrotszyDystans = min(najkrotszyDystans, minDroga[(1 << ileWiosek) - 1][i] + macierzOdleglosci[i][0]);
    }

    return najkrotszyDystans;
}

int main()
{
    int ileTestow = 0;
    scanf("%d\n", &ileTestow);

    while (ileTestow--)
    {
        int ileWiosek = 0;
        scanf("%d ", &ileWiosek); // Wczytanie liczby wiosek

        vector<pair<int, int>> wioski(ileWiosek);
        char nawias = 0;
        scanf("%c", &nawias);

        for (int i = 0; i < ileWiosek; ++i)
        {
            int x, y;
            scanf("(%d,%d)", &x, &y);
            wioski[i] = {x, y};

            if (i < ileWiosek - 1)
            {
                scanf("%c", &nawias); // Wczytywanie przecinka między punktami
            }
        }

        scanf("%c", &nawias); // Końcowy nawias

        double wynik = najkrotszaDroga(ileWiosek, wioski);
        printf("%d\n", (int)floor(wynik));
    }

    return 0;
}