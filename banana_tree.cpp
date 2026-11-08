#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

// Funkcja sprawdza, czy drzewo jest bananowe i zwraca liczbę bananów (liści),
// albo 0 jeśli nie jest bananowe
int ileBananow(int liczbaWierzcholkow, const vector<vector<int>> &macierzSasiedztwa)
{

    // Graf z 1 wierzchołkiem nie może być bananowym drzewem, bo nie da się zbudować gwiazdy
    if (liczbaWierzcholkow <= 1)
        return 0;

    // Jeśli są 2 wierzchołki i połączenie między nimi, traktujemy to jako „małą gwiazdę”, czyli 1 banan, 1 korzeń → razem 2 banany
    if (liczbaWierzcholkow == 2)
        return (macierzSasiedztwa[0][1] == 1 && macierzSasiedztwa[1][0] == 1) ? 2 : 0;

    // Liczymy stopnie każdego wierzchołka, czyli ile sąsiadów ma każdy wierzchołek, bo to jego stopień
    vector<int> stopnieW(liczbaWierzcholkow, 0);
    for (int i = 0; i < liczbaWierzcholkow; ++i)
        for (int j = 0; j < liczbaWierzcholkow; ++j)
            if (macierzSasiedztwa[i][j])
                stopnieW[i]++;

    // Dzielimy wierzchołki na liście (stopień 1, czyli wtedy banany), a jeśli nie to wtedy to potencjalny korzeń lub centrum gwiazdy
    vector<int> liscie, srodekLubKorzen;
    for (int i = 0; i < liczbaWierzcholkow; ++i)
    {
        if (stopnieW[i] == 1)
            liscie.push_back(i);
        else
            srodekLubKorzen.push_back(i);
    }

    // Jeśli nie ma liści – to nie może być drzewo bananowe
    if (liscie.empty())
        return 0;

    // Jeśli jest tylko jedno centrum – mamy gwiazdę – to jest drzewo bananowe
    if (srodekLubKorzen.size() == 1)
        return liscie.size();

    // Sprawdzamy czy gwaizda ma poprawną strukturę
    // Sprawdzamy każde centrum jako potencjalny korzeń
    for (int potencjalnyKorzen : srodekLubKorzen)
    {
        bool poprawnyKorzen = true;
        set<int> rozneStopnieCentrow;

        for (int wierzcholek : srodekLubKorzen)
        {
            if (wierzcholek == potencjalnyKorzen)
                continue;

            // Środek gwiazdy musi być połączony z korzeniem
            if (macierzSasiedztwa[wierzcholek][potencjalnyKorzen] != 1)
            {
                poprawnyKorzen = false;
                break;
            }

            // Środek gwiazdy może być połączony tylko z liśćmi i korzeniem
            for (int j = 0; j < liczbaWierzcholkow; ++j)
            {
                if (macierzSasiedztwa[wierzcholek][j] == 1 && j != potencjalnyKorzen)
                {
                    if (stopnieW[j] != 1)
                    {
                        poprawnyKorzen = false;
                        break;
                    }
                }
            }

            rozneStopnieCentrow.insert(stopnieW[wierzcholek]);
        }

        // Liście nie mogą być połączone bezpośrednio z korzeniem
        for (int lisc : liscie)
        {
            if (macierzSasiedztwa[lisc][potencjalnyKorzen] == 1)
            {
                poprawnyKorzen = false;
                break;
            }
        }

        // Jeśli wszystkie centra mają ten sam stopień i są poprawnie podłączone
        if (poprawnyKorzen && rozneStopnieCentrow.size() <= 1)
            return liscie.size();
    }

    // Jeśli żaden kandydat nie spełnił warunków
    return 0;
}

int main()
{
    int liczbaTestow;
    cin >> liczbaTestow;

    // Wczytywanie danych
    while (liczbaTestow--)
    {
        int liczbaWierzcholkow;
        string wejscieMacierzy;
        cin >> liczbaWierzcholkow >> wejscieMacierzy;

        // Zamiana ciągu znaków na macierz sąsiedztwa
        vector<vector<int>> macierz(liczbaWierzcholkow, vector<int>(liczbaWierzcholkow));
        for (int i = 0; i < liczbaWierzcholkow * liczbaWierzcholkow; ++i)
        {
            macierz[i / liczbaWierzcholkow][i % liczbaWierzcholkow] = wejscieMacierzy[i] - '0';
        }

        int liczbaBananow = ileBananow(liczbaWierzcholkow, macierz);
        if (liczbaBananow > 0)
            cout << liczbaBananow << " bananas :)" << endl;
        else
            cout << "0 bananas :(" << endl;
    }

    return 0;
}