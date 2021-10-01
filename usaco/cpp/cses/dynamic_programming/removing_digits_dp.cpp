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

#define MAX_POW_10 7

int main() {
    int input;
    cin >> input;
    vi dp(input+1);
    FOR(i, 1, input+1) {
        int val = INT_MAX;
        FOR(j, 1, MAX_POW_10)
        {
            int modVal = (i % (int)pow(10, j)) / (int)pow(10, j - 1);
            if (modVal)
                val = min(val, dp[i - modVal] + 1);
        }
        dp[i] = val;
    }
    cout << dp[input] << endl;
    return 0;
}