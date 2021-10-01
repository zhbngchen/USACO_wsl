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

using vsi = vector<unordered_set<int>>;
using vvb = vector<vector<bool>>;

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

int main() {
    int N;
    cin >> N;
    vvi inputs(N);
    FOR(i,0,N) {
        inputs[i].resize(N);
        FOR(j,0,N) {
            cin >> inputs[i][j];
        }
    }

    int horizontalMax=0;
    FOR(i, 0, N) {
        vi horizontalSum(2);
        FOR(j, 0, N) {
            horizontalSum[j%2] += inputs[i][j];
        }
        horizontalMax += max(horizontalSum[0], horizontalSum[1]);
    }

    int verticalMax=0;
    FOR(j, 0, N) {
        vi verticalSum(2);
        FOR(i, 0, N) {
            verticalSum[i%2] += inputs[i][j];
        }
        verticalMax += max(verticalSum[0], verticalSum[1]);
    }

    cout << max(horizontalMax, verticalMax) << endl;

    return 0;
}