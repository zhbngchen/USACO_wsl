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

int recursive(int x, int bookIndex, int n) {
    if (bookIndex == n || x == 0)
        return 0;
    if (dp[x][bookIndex] != -1)
        return dp[x][bookIndex];
    int ret = 0;
    FOR(i, bookIndex, n) {
        if (prices[i] <= x) {
            ret = max(ret, pages[i] + recursive(x - prices[i], i + 1, n));
        }
    }
    dp[x][bookIndex] = ret;
    return ret;
}

int main() {
    int n, x;
    cin >> n >> x;;
    dp.resize(x+1, vi(n, -1));
    prices.resize(n);
    FOR(i, 0, n)
        cin >> prices[i];
    pages.resize(n);
    FOR(i, 0, n)
        cin >> pages[i];

    cout << recursive(x, 0, n) << endl;
    return 0;
}