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

typedef vector<pii> vpii;
typedef vector<char> vc;

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

#define __SUBMIT

#ifndef __SUBMIT
    ifstream fIn("1.in");
    ofstream fOut("1.out");
    #define cin fIn
    #define cout fOut
#endif


int N;
vi inputs;

int findCeilingLog2(int val) {
    int ret = 0;
    int result = 1;
    while (result < val) {
        result <<= 1;
        ret++;
    }
    return ret;
}

int main() {
    cin >> N;
    inputs.resize(N+1);
    FOR(i, 0, N-1) {
        int x, y;
        cin >> x >> y;
        inputs[x]++;
        inputs[y]++;
    }

    int ret = findCeilingLog2(inputs[1] + 1);
    FOR(i, 2, N+1)
        ret += findCeilingLog2(inputs[i]) + 1;

    cout << ret << endl;

    return 0;
}