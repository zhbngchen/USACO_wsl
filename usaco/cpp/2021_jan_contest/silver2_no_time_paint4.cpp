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

const int numColors = 27; // 0 is empty, 1 is 'A', 2 is 'B', ..., 26 is 'Z'

int main() {
    int N, Q;
    cin >> N >> Q;
    string inputs;
    cin >> inputs;
    vpii ranges(Q);
    FOR(i,0,Q)
        cin >> ranges[i].first >> ranges[i].second;
    
    vb colorStatusActive(numColors);
    vi strokes(N+1);

    FOR(i, 1, N+1) {
        int colorIndex = inputs[i-1] - 'A' + 1;
        strokes[i] = strokes[i-1];
        FOR(j, 1, numColors)
            if (colorIndex < j)
                colorStatusActive[j] = false;
        if (!colorStatusActive[colorIndex])
            strokes[i] ++;
        colorStatusActive[colorIndex] = true;
    }

    vb colorStatusActiveReverse(numColors);
    vi strokesReverse(N+2);

    for (int i = N; i >= 1; i--) {
        int colorIndex = inputs[i-1] - 'A' + 1;
        strokesReverse[i] = strokesReverse[i+1];
        FOR(j, 1, numColors)
            if (colorIndex < j)
                colorStatusActiveReverse[j] = false;
        if (!colorStatusActiveReverse[colorIndex])
            strokesReverse[i]++;
        colorStatusActiveReverse[colorIndex] = true;
    }

    FOR(i, 0, Q) {
        int result = 0;
        int start = ranges[i].first;
        int end = ranges[i].second;
        result += strokes[start - 1];
        result += strokesReverse[end+1];
        cout << result << endl;
    }
    return 0;
}