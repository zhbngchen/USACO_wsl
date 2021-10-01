#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    int N, M, R;

    ifstream fin("rental.in");
    fin >> N >> M >> R;

    vector<int> produces(N);

    struct Purchase
    {
        int gallons;
        int pricePerGallon;
    };

    vector<Purchase> purchases(M);

    vector<int> rents(R);

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

    vector<long long> purchaseResults(N);

    for (int i = 0, indPurchase = 0, curPurchase = purchases[0].gallons; i < N; i++)
    {
        if (i)
        {
            purchaseResults[i] = purchaseResults[i - 1];
        }

        if (indPurchase >= purchases.size())
        {
            continue;
        }
        
        int curProduct = produces[i];
        if (curProduct < curPurchase)
        {
            purchaseResults[i] += curProduct * purchases[indPurchase].pricePerGallon;
            curPurchase -= curProduct;
        }
        else
        {
            while (curProduct >= curPurchase && indPurchase < purchases.size())
            {
                int lastProduct = min(curPurchase, curProduct);
                curProduct -= lastProduct;
                purchaseResults[i] += lastProduct * purchases[indPurchase++].pricePerGallon;
                curPurchase = purchases[indPurchase].gallons;
            }
            curPurchase -= curProduct;
            if (indPurchase < purchases.size())
            {
                purchaseResults[i] += curProduct * purchases[indPurchase].pricePerGallon;
            }
        }
    }

    long long rentResults = 0;
    long long result = purchaseResults[N - 1];
    for (int i = 0, j = N - 2; i < R && j >= 0; i++, j--)
    {
        rentResults += rents[i];
        long long curRentPlusPurchase = rentResults + purchaseResults[j];
        if (result < curRentPlusPurchase)
        {
            result = curRentPlusPurchase;
        }
    } 
    ofstream fout("rental.out");
    fout << result << endl;
    return 0;
}