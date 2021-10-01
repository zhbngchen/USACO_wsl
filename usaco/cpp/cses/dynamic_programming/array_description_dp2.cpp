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

#define KEY_BASE1 100000 // 10^5
#define KEY_BASE2 10000000 // 10^7
#define MOD (int)(1e9+7)
unordered_map<int, int> dp2;

int main() {
    int n,m;
    cin >> n >> m;
    vi inputs(n);
    FOR(i,0,n)
        cin >> inputs[i];
    vector<vector<ll>> dp(n, vector<ll>(m+1));
    if (inputs[0] == 0)
        FOR(i,1,m+1)
            dp[0][i] = 1;
    else
        dp[0][inputs[0]] = 1;    
    FOR(i,1,n) {
        if (inputs[i] == 0) {
            FOR(j,1,m+1) {
                dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
                if (j < m)
                    dp[i][j] += dp[i-1][j+1];
                dp[i][j] %= MOD;
            }
        }
        else {
            dp[i][inputs[i]] = dp[i-1][inputs[i]] + dp[i-1][inputs[i] - 1];
            if (inputs[i] < m)
                dp[i][inputs[i]] += dp[i-1][inputs[i] + 1];
            dp[i][inputs[i]] %= MOD;
        }
    }

    ll result = 0;
    if (inputs[n-1] != 0)
        result = dp[n-1][inputs[n-1]];
    else
        FOR(i,1,m+1)
            result += dp[n-1][i];
    result %= MOD;
    cout << (int)result << endl;

    return 0;
}