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

int a, b, sum;

vvi memo;

int main() {
    cin >> a >> b;
    memo.resize(a + 1, vi(b+1, INT_MAX));
    FOR(i, 1, a+1) {
        FOR(j, 1, b+1) {
            if (i == j) {
                memo[i][j] = 0;
            }
            FOR(k, 1, i) {
                memo[i][j] = min(memo[i][j], memo[k][j] + memo[i-k][j] + 1);
            }
            FOR(k, 1, j) {
                memo[i][j] = min(memo[i][j], memo[i][k] + memo[i][j-k] + 1);
            }
        }
    }
    cout << memo[a][b] << endl;
    return 0;
}