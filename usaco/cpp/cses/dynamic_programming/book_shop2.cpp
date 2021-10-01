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
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

#ifdef __LOCAL
    ifstream fin("in");
    ofstream fout("out");
    #define cin fin
    #define cout fout
#endif

vi prices;
vi pages;

vvi dp;

int recursive(int x, int bookIndex) {
    if (bookIndex == 0 || x == 0)
        return 0;
    if (dp[bookIndex][x] != -1)
        return dp[bookIndex][x];
    int ret = 0;
    if (prices[bookIndex] <= x)
    {
        ret = max(ret, pages[bookIndex] + recursive(x - prices[bookIndex], bookIndex - 1));
    }
    ret = max(ret, recursive(x, bookIndex - 1));
    dp[bookIndex][x] = ret;
    return ret;
}

int main() {
    int n, x;
    cin >> n >> x;;
    dp.resize(n+1, vi(x+1, -1));
    prices.resize(n+1);
    FOR(i, 1, n+1)
        cin >> prices[i];
    pages.resize(n+1);
    FOR(i, 1, n+1)
        cin >> pages[i];

    cout << recursive(x, n) << endl;
    return 0;
}