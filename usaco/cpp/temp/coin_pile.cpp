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

bool calc(int a, int b) {
    if (!a && !b)
        return true;
    else if (a == 1 && b == 2 || a == 2 && b == 1)
        return true;
    int diff = abs(a-b);
    int other;
    if (a > b)
        other = b - diff;
    else
        other = a - diff;
    if (other >= 0 && other % 3 == 0)
        return true;
    else
        return false;
}

int main() {
    int n;
    cin >> n;
    FOR(i,0,n) {
        int a, b;
        cin >> a >> b;
        if (calc(a, b))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}