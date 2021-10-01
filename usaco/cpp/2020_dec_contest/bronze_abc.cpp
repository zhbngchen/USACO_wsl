#include <bits/stdc++.h>

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

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

int main() {
    vi inputs;
    int n;
    while (cin >> n) {
        inputs.push_back(n);
    }

    sort(inputs.begin(), inputs.end());
    int a = inputs[0];
    int b = inputs[1];
    int c = inputs[2] == (a+b) ? inputs[3] : inputs[2];
    cout << a << ' ' << b << ' ' << c << endl;
    return 0;
}