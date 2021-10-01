/*
PROG: shopping
LANG: C++
*/

#include "bits/stdc++.h"
#include <math.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef set<int> si;
typedef map<string, int> msi;
typedef map<int, int> mii;
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a))

struct Offer {
    int items[5];
    int price;
};

int main() {
    ofstream fout("shopping.out");
    ifstream fin("shopping.in");
    int s;
    fin >> s;
    mii indexes;
    int index = 0;
    vector<Offer> offers(s);
    FOR(i, 0, s)
    {
        int n;
        fin >> n;
        FOR(j, 0, n)
        {
            int c, k;
            fin >> c >> k;
            if (indexes.find(c) == indexes.end())
                indexes[c] = index ++;
            offers[i].items[indexes[c]] = k;
        }
        fin >> offers[i].price;
    }
    int b;
    fin >> b;
    offers.resize(s+b);
    vi items(5);
    FOR(i, 0, b)
    {
        int c, k, p;
        fin >> c >> k >> p;
        if (indexes.find(c) == indexes.end())
            indexes[c] = index ++;
        offers[s+i].items[indexes[c]] = 1;
        offers[s+i].price = p;
        items[indexes[c]] = k;
    }

    int memo[6][6][6][6][6];
    memset(memo, 0x77, sizeof(memo));
    memo[0][0][0][0][0] = 0;

    FOR(i,0,s+b)
        FOR(j,0,5)
            FOR(k,0,5)
                FOR(l,0,5)
                    FOR(m,0,5) 
                        FOR(n,0,5) {
                            int j2 = j + offers[i].items[4];
                            int k2 = k + offers[i].items[3];
                            int l2 = l + offers[i].items[2];
                            int m2 = m + offers[i].items[1];
                            int n2 = n + offers[i].items[0];
                            if (j2<6 && k2<6 && l2<6 && m2<6 && n2<6 && memo[j2][k2][l2][m2][n2] > memo[j][k][l][m][n] + offers[i].price)
                                memo[j2][k2][l2][m2][n2] = memo[j][k][l][m][n] + offers[i].price;
                        }
    fout << memo[items[4]][items[3]][items[2]][items[1]][items[0]] << endl;
    return 0;
}