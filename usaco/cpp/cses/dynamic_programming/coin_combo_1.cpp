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
vi visited;

int recursive(int x) {
    if (visited[x])
        return visited[x];
    ll result = 0;
    for(auto coin: coins) {
        if (x == coin) {
            result += 1;
        }
        else if (x > coin) {
            result += recursive(x-coin);
        }
    }
    result %= (int)pow(10,9) + 7;
    visited[x] = (int)result;
    return (int)result;
}

int main() {
    cin >> n >> x;
    coins.resize(n);
    visited.resize(x+1);
    FOR(i,0,n)
        cin >> coins[i];
    sort(coins.begin(), coins.end(), greater<int>());
    cout << recursive(x) << endl;
    return 0;
}