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
unordered_map<int, int> dp;

int recursive(int begin, int end, int level, int unknownCount, int m) {
    vi deltas = {-1, 0, 1};
    if (end == 0 && level == unknownCount || level == unknownCount+1) {
        if (begin == end || end == 0)
            return 1;
        else
            return 0;
    }
    int ret = 0;
    if (begin) {
        FOR(i, 0, 3)
        {
            int next = begin + deltas[i];
            if (next && next <= m)
            {
                ret += recursive(next, end, level + 1, unknownCount, m);
            }
        }
    }
    else {
            FOR(j, 1, m+1) {
                int next = j;
                ret += recursive(next, end, level + 1, unknownCount, m);
            }
    }
    return ret;
}

int calc(int begin, int end, int unknownCount, int m) {
    int key = end * KEY_BASE2 + begin * KEY_BASE1 + unknownCount;
    if (dp[key])
        return dp[key];

    int ret = recursive(begin, end, 0, unknownCount, m) % MOD;
    dp[key] = ret;
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
    int result = 1;
    FOR(i,0,n) {
        if (array[i] == 0)
            unknownCount ++;
        else {
            if (unknownCount) {
                if (beginIndex == -1) {
                    result *= calc(array[i], 0, unknownCount, m);
                }
                else
                {
                    result *= calc(array[beginIndex], array[i], unknownCount, m);
                }
                unknownCount = 0;
            }
            if (beginIndex != -1 && i == beginIndex + 1 && abs(array[i] - array[beginIndex]) > 1) {
                unknownCount = 0;
                result = 0;
                break;
            }
            beginIndex = i;
        }
    }
    if (unknownCount)
        result *= calc(array[beginIndex], 0, unknownCount, m);
    else if (beginIndex == -1)
        result = 0;

    cout << result << endl;

    return 0;
}