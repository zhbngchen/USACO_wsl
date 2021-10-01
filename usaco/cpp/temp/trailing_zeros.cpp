#include <bits/stdc++.h>
#include <math.h>

using namespace std;

typedef long long ll; 
typedef pair<int, int> pii; 
typedef pair<ll, ll> pll; 
typedef pair<string, string> pss; 
typedef vector<int> vi; 
typedef vector<vi> vvi;  
typedef vector<ll> vl; 
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef unordered_set<int> si; 
typedef unordered_map<string, int> msi;
typedef unordered_map<int, int> mii;

typedef vector<pii> vpii;
typedef vector<char> vc;
typedef vector<vc> vvc;


using vsi = vector<unordered_set<int>>;
using vvb = vector<vector<bool>>;

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

#ifdef __LOCAL
    ifstream fIn("in");
    ofstream fOut("out");
    #define cin fIn
    #define cout fOut
#endif

int main() {
    int n;
    cin >> n;
    
    int result = 0;
    n = n - n%5;
    for (int i = n; i >= 5; i-=5)
    {
        int modVal = i % 10;
        int tempi = i/10;
        while (!modVal) {
            result ++;
            modVal = tempi % 10;
            tempi /= 10;
        }
        while (modVal == 5) {
            result ++;
            tempi *= 2;
            tempi += 1;
            modVal = tempi % 10;
            tempi /= 10;
        }
    }
    cout << result << endl;

    return 0;
}