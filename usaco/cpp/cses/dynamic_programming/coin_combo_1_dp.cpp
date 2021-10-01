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

int n, x;
vi coins;
vector<ll> dp;

int main() {
    cin >> n >> x;
    coins.resize(n);
    dp.resize(x+1);
    FOR(i,0,n)
        cin >> coins[i];
    //sort(coins.begin(), coins.end());
    FOR(i,1,x+1) {
        FOR(j,0,n) {
            int diff = i - coins[j];
            if (diff == 0)
                dp[i] += 1;
            else if (diff > 0) {
                dp[i] += dp[diff];
            }
            dp[i] %= (int)pow(10,9) + 7;
        }
    }
    cout << dp[x] << endl;
    return 0;
}