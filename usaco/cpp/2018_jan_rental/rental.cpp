#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int N, M, R;

vector<int> produces;
vector<int> rents;

struct Purchase
{
    int gallons;
    int pricePerGallon;
};

vector<Purchase> purchases;

int main()
{
    ifstream fin("rental.in");
    fin >> N >> M >> R;
    produces.resize(N);
    purchases.resize(M);
    rents.resize(R);
    for (int i = 0; i < N; i++)
    {
        fin >> produces[i];
    }
    for (int i = 0; i < M; i++)
    {
        fin >> purchases[i].gallons >> purchases[i].pricePerGallon;
    }
    for (int i = 0; i < R; i++)
    {
        fin >> rents[i];
    }

    sort(produces.begin(), produces.end(), [](const int x, const int y) { return x > y;});
    sort(purchases.begin(), purchases.end(), [](const Purchase& p1, const Purchase& p2) {return p1.pricePerGallon > p2.pricePerGallon;});
    sort(rents.begin(), rents.end(), [](const int x, const int y) { return x > y;});

    long long result = 0;
    int i = 0, j = N - 1;
    int indPurchase = 0, indRents = 0;
    while (i <= j && (indRents < rents.size() || indPurchase < purchases.size()))
    {
        if (indRents < rents.size() && indPurchase >= purchases.size())
        {
            result += rents[indRents++];
            j--;
        }
        else if (indRents >= rents.size() && indPurchase < purchases.size())
        {
            if (produces[i] < purchases[indPurchase].gallons)
            {
                result += produces[i] * purchases[indPurchase].pricePerGallon;
                purchases[indPurchase].gallons -= produces[i++];
            }
            else
            {
                result += purchases[indPurchase].gallons * purchases[indPurchase].pricePerGallon;
                produces[i] -= purchases[indPurchase++].gallons;
            }
        }
        else if (produces[i] < purchases[indPurchase].gallons)
        {
            if (produces[i] * purchases[indPurchase].pricePerGallon >= rents[indRents])
            {
                result += produces[i] * purchases[indPurchase].pricePerGallon;
                purchases[indPurchase].gallons -= produces[i++];
            }
            else
            {
                result += rents[indRents++];
                j--;
            }
        }
        else if (indPurchase < purchases.size() || indRents < rents.size())
        {
            int cows = produces[i];
            long long cost = 0;
            int copyIndPurchase = indPurchase;
            int lastCows;
            while (indPurchase < purchases.size())
            {
                lastCows = min(purchases[copyIndPurchase].gallons, cows);
                cost += lastCows * purchases[copyIndPurchase].pricePerGallon;
                cows -= lastCows;
                if (cows == 0)
                {
                    purchases[copyIndPurchase].gallons -= lastCows;
                    break;
                }
                else
                {
                    copyIndPurchase++;
                }
            }
            while (i <= j && indRents < rents.size() && cost <= rents[indRents])
            {
                result += rents[indRents++];
                j--;
            }

            if (i <= j)
            {
                result += cost;
                indPurchase = copyIndPurchase;
                i++;
            }
        }
    }
    ofstream fout("rental.out");
    fout << result << endl;
    return 0;
}