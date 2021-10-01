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

int result = INT_MAX;
int n, x;
vi coins;
vb visited;

void recursive(int x, int count) {
    if (visited[x])
        return;
    for(auto coin: coins) {
        if (x == coin) {
            if (result > (count+1))
                result = count + 1;
            return;
        }
        else if (x > coin) {
            recursive(x - coin, count + 1);
            visited[x - coin] = true;
        }
    }
}

int main() {
    cin >> n >> x;
    coins.resize(n);
    visited.resize(x+1);
    FOR(i,0,n)
        cin >> coins[i];
    sort(coins.begin(), coins.end(), greater<int>());
    recursive(x, 0);
    if (result == INT_MAX)
        result = -1;
    cout << result << endl;
    return 0;
}