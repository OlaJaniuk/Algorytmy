#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cstring>
#include <cstdint>

using namespace std;

// Funkcja do szybkiego wczytywania liczby caÅkowitej
inline int wczytajLiczbe()
{
    int znak = getchar(), liczba = 0;
    while (znak < '0' || znak > '9')
        znak = getchar();
    do
    {
        liczba = liczba * 10 + (znak - '0');
        znak = getchar();
    } while (znak >= '0' && znak <= '9');
    return liczba;
}

// przenoÅna funkcja zliczajÄca bity ustawione w uint64_t (popcount)
inline int zliczBity(uint64_t x)
{
    // Kernighanâs algorithm
    int licznik = 0;
    while (x)
    {
        x &= (x - 1);
        ++licznik;
    }
    return licznik;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int liczbaTestow = wczytajLiczbe();
    while (liczbaTestow--)
    {
        int liczbaWierzcholkow = wczytajLiczbe();
        int liczbaScian = wczytajLiczbe();

        int liczbaSlow = (liczbaWierzcholkow + 63) >> 6; // liczba 64âbitowych sÅÃłw na wiersz, bo >>6 to dzielenie przez 2^6 czyli przez 64

        // taSamaSciana[u][w] = 1, jeÅli u i v=w*64+bit sÄ na tej samej Åcianie
        vector<vector<uint64_t>> taSamaSciana(liczbaWierzcholkow, vector<uint64_t>(liczbaSlow, 0));

        // Wczytanie Åcian i sprawdzenie co jest na tej samej Åcianie
        for (int i = 0; i < liczbaScian; i++)
        {
            int ileWNaScianie = wczytajLiczbe();
            vector<int> sciana(ileWNaScianie);

            for (int j = 0; j < ileWNaScianie; j++)
            {
                sciana[j] = wczytajLiczbe();
            }

            for (int a = 0; a < ileWNaScianie; a++)
            {
                int u = sciana[a];

                for (int b = 0; b < ileWNaScianie; b++)
                {
                    int v = sciana[b];
                    if (u != v)
                        taSamaSciana[u][v >> 6] |= (1ULL << (v & 63)); // to znaczy, Åźe sÄ na tej samej Åcianie
                }
            }
        }

        // budujemy graf przekatnych G
        vector<vector<uint64_t>> G(liczbaWierzcholkow, vector<uint64_t>(liczbaSlow, 0));
        for (int u = 0; u < liczbaWierzcholkow; u++)
        {
            for (int w = 0; w < liczbaSlow; w++)
            {
                G[u][w] = ~taSamaSciana[u][w]; // negacja bitowa, czyli dopeÅnienie
            }

            // wyzeruj pÄtlÄ (u,u)
            G[u][u >> 6] &= ~(1ULL << (u & 63));

            if (liczbaWierzcholkow & 63) // jeÅli ostatnie sÅowo zawiera niepeÅne 64 bity
            {
                int poprawny = liczbaWierzcholkow & 63;
                G[u][liczbaSlow - 1] &= ((1ULL << poprawny) - 1); // zerowanie nadmiarowych bitÃłw
            }
        }

        // liczba potencjalnych 4âcykli
        long long liczbaCykli = 0;
        for (int u = 0; u < liczbaWierzcholkow; u++)
        {
            for (int v = u + 1; v < liczbaWierzcholkow; v++)
            {
                long long wspolniSasiedzi = 0;
                for (int w = 0; w < liczbaSlow; w++)
                {
                    wspolniSasiedzi += zliczBity(G[u][w] & G[v][w]);
                }
                if (wspolniSasiedzi >= 2)
                    liczbaCykli += wspolniSasiedzi * (wspolniSasiedzi - 1) / 2;
            }
        }

        // kaÅźdy cykl policzony dwukrotnie â dzielimy przez 2
        cout << (liczbaCykli / 2) << '\n';
    }
    return 0;
}