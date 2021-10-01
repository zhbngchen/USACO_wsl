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

int calc(int begin, int end, int unknownCount, int m) {
    int key = end * KEY_BASE2 + begin * KEY_BASE1 + unknownCount;
    if (dp2[key])
        return dp2[key];

    vector<vector<ll>> dp(unknownCount+2, vector<ll>(m+2));
    int endIndex = unknownCount+1;
    if (begin == 0) {
        FOR(i,1,m+1) {
            dp[0][i] = 1;
        }
        endIndex --;
    }
    else
    {
        dp[0][begin] = 1;
    }
    
    FOR(i,1,unknownCount+2) {
        FOR(j,1,m+1) {
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1]) % MOD;
        }
    }
    ll ret = 0;
    if (end == 0) {
        endIndex --;
        FOR(i,1,m+1) {
            ret += dp[endIndex][i];
            ret %= MOD;
        }
    }
    else
    {
        ret = dp[endIndex][end];
    }
    
    dp2[key] = ret;
    return ret;
}

int main() {
    int n,m;
    cin >> n >> m;
    vi array(n);
    FOR(i,0,n)
        cin >> array[i];
    int unknownCount = 0;
    int beginIndex = -1;
    ll result = 1;
    FOR(i,0,n) {
        if (array[i] == 0)
            unknownCount ++;
        else {
            if (unknownCount) {
                if (beginIndex == -1) {
                    result *= calc(0, array[i], unknownCount, m);
                }
                else
                {
                    result *= calc(array[beginIndex], array[i], unknownCount, m);
                }
                result %= MOD;
                unknownCount = 0;
            }
            if (beginIndex != -1 && i == beginIndex + 1 && abs(array[i] - array[beginIndex]) > 1) {
                unknownCount = 0;
                result = 0;
                break;
            }
            beginIndex = i;
            //if (i > 50000)
            //    cout << "test" << endl;
        }
    }
    if (unknownCount) {
        if (beginIndex == -1)
            result *= calc(0, 0, unknownCount, m);
        else
            result *= calc(array[beginIndex], 0, unknownCount, m);
    }
    else if (beginIndex == -1)
        result = 0;

    result %= MOD;
    cout << (int)result << endl;

    return 0;
}