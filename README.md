# Algorytmy i Optymalizacje Bitowe w C++

## Opis projektu
Zbiór zaawansowanych rozwiązań problemów algorytmicznych i grafowych, zaimplementowanych w języku C++. Główne nacisk w projektach położono na ekstremalną optymalizację pamięciową, wykorzystanie operacji bitowych oraz programowanie dynamiczne.

## Zawartość repozytorium i zastosowane techniki

* **Przekątne w wielościanach (diagonals.cpp):**
  Poszukiwanie 4-cykli w grafach przestrzennych. Zastosowano kompresję macierzy sąsiedztwa do 64-bitowych słów (`uint64_t`). Do błyskawicznego obliczania części wspólnych zbiorów wierzchołków wykorzystano maski bitowe oraz autorską implementację algorytmu Kernighana (popcount).

* **Problem Komiwojażera - TSP (tsp_tarzan.cpp):**
  Znajdowanie najkrótszej ścieżki w grafie. Zamiast naiwnego algorytmu siłowego $O(n!)$, zaimplementowano programowanie dynamiczne z użyciem masek bitowych (algorytm Helda-Karpa), znacząco redukując złożoność obliczeniową do $O(n^2 2^n)$.

* **Problem Josephusa (josephus.cpp):**
  Rozwiązanie problemu eliminacji w kółku. Optymalizacja polega na użyciu przesunięć bitowych do szybkiego wyznaczania potęg dwójki, co pozwala na rozwiązanie w czasie $O(1)$ dla specyficznych przypadków brzegowych przed przejściem do symulacji na tablicach dynamicznych.

* **Drzewa Bananowe i Grafy Collatza (banana_tree.cpp, collatz.cpp):**
  Algorytmy rozpoznające specyficzne struktury grafowe (gwiazdy, kliki) na podstawie macierzy sąsiedztwa i wektorów stopni wierzchołków, bez użycia gotowych bibliotek grafowych.

## Technologie
* Język: C++17
* Paradygmaty: Programowanie dynamiczne (Bitmask DP), teoria grafów, arytmetyka wskaźników, bit-level memory efficiency.

## Kompilacja
Każdy plik stanowi niezależny program. Aby skompilować wybrany algorytm, należy użyć standardowego kompilatora:
```bash
g++ diagonals.cpp -o diagonals -std=c++17 -O3