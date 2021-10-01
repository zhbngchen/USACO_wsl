#include "bits/stdc++.h"
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

int n, x;
vi coins;
vi dp;

int main() {
    cin >> n >> x;
    coins.resize(n);
    dp.resize(x+1, INT_MAX);
    FOR(i,0,n)
        cin >> coins[i];
    //sort(coins.begin(), coins.end());
    FOR(i,1,x+1) {
        FOR(j,0,n) {
            int last_index = i - coins[j];
            if (last_index < 0)
                continue;
            else if (i-coins[j] == 0)
                dp[i] = 1;
            else if (dp[last_index] != INT_MAX && dp[i] > dp[last_index] + 1)
                dp[i] = dp[last_index] + 1;
        }
    }
    if (dp[x] == INT_MAX)
        cout << -1 << endl;
    else
        cout << dp[x] << endl;
    return 0;
}