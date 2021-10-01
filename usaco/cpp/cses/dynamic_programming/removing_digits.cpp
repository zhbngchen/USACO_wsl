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

vi dp;
int recursive(int x) {
    if (dp[x])
        return dp[x];

    if (x == 0)
        return 0;
    int ret = INT_MAX;
    FOR(i, 1, MAX_POW_10) {
        int modVal = (x % (int)pow(10, i)) / (int)pow(10, i - 1);
        if (modVal)
            ret = min(ret, recursive(x - modVal)+1);
    }
    dp[x] = ret;
    return ret;
}

int main() {
    int input;
    cin >> input;
    dp.resize(input + 1);
    cout << recursive(input) << endl;
    return 0;
}