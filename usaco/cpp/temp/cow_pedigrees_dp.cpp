/*
PROG: nocows
LANG: C++
*/

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

int main() {
    ofstream fout ("nocows.out");
    ifstream fin ("nocows.in");
    int N, K;
    fin >> N >> K;
    vvi dp(N+1, vi(K+1));
    FOR(i,1,K+1)
        dp[1][i] = 1;
    int i = 3;
    while (i <= N) {
        FOR(j,1,K+1) {
            int k = 1;
            while (k < i) {
                dp[i][j] += dp[k][j-1] * dp[i - 1 - k][j-1];
                dp[i][j] %= 9901;
                k += 2;
            }
        }
        i += 2;
    }
    fout << (dp[N][K] + 9901 - dp[N][K-1])%9901 << endl;
    return 0;
}