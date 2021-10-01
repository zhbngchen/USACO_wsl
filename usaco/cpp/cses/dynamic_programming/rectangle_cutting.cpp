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

int recursion(int lvl, int l, int h) {
    if (l == h) {
        return 0;
    }
    if (memo[l][h] != 0) {
        return memo[l][h];
    }
    int minimum = INT_MAX;
    FOR(i, 1, l/2+1) {
        sum = recursion(lvl + 1, i, h) + recursion(lvl+1, l-i, h) + 1;
        minimum = min(sum, minimum);
    }
    FOR(i, 1, h/3+1) {
        sum = recursion(lvl + 1, l, i) + recursion(lvl + 1, l, h-i) + 1;
        minimum = min(sum, minimum);
    }
    memo[l][h] = minimum;
    return minimum;
}

int main() {
    cin >> a >> b;
    memo.resize(a + 1, vi(b+1));
    int result = recursion(0, a, b);
    cout << result << endl;
    return 0;
}