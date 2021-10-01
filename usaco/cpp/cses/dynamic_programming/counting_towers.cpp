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

#define MOD (int)(1e9+7)

#ifdef __LOCAL
    ifstream fin("in");
    ofstream fout("out");
    #define cin fin
    #define cout fout
#endif

int main() {
    int n;
    cin >> n;
    vi inputs(n);
    int maxInput = 0;
    FOR(i,0,n) {
        cin >> inputs[i];
        if (inputs[i] > maxInput)
            maxInput = inputs[i];
    }

    vector<vector<ll>> dp(maxInput, vector<ll>(6));
    dp[0][2] = 1;
    dp[0][3] = 1;
    vector<vi> nextItems = {{0, 2, 3}, 
                            {1, 2, 3, 4, 5},
                            {0, 2, 3}, 
                            {1, 2, 3, 4, 5},
                            {1, 2, 3, 4, 5},
                            {1, 2, 3, 4, 5}};
    FOR(i,1,maxInput) {
        FOR(j,0,6) {
            FOR(k,0,nextItems[j].size()) {
                dp[i][nextItems[j][k]] += dp[i-1][j];
            }
        }
        FOR(j,0,6)
            dp[i][j] %= MOD;
    }

    FOR(i,0,n) {
        ll result = 0;
        FOR(j,0,6)
            result += dp[inputs[i]-1][j];
        result %= MOD;
        cout << (int)result << endl;
    }
    return 0;
}