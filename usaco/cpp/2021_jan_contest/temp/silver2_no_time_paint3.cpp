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

const int numColors = 26;

int main() {
    int N, Q;
    cin >> N >> Q;
    string inputs;
    cin >> inputs;
    vpii ranges(Q);
    FOR(i,0,Q)
        cin >> ranges[i].first >> ranges[i].second;
    
    vvi colorPos(numColors);
    FOR(i,0,inputs.size()) {
        int index = inputs[i] - 'A';
        
        colorPos[index].push_back(i+1);
    }

    vi lastColorIndex(numColors);
    vi strokes(inputs.size());

    strokes[0] = 1;
    lastColorIndex[inputs[0] - 'A'] = 1;
    FOR(i, 1, inputs.size()) {
        int position = i+1;
        int colorIndex = inputs[i] - 'A';
        bool hit = false;
        if (colorIndex == 0 && lastColorIndex[colorIndex] == 0) {
            strokes[i] = strokes[i-1] + 1;
            hit = true;
        }
        FOR(j, 0, colorIndex) {
            if (lastColorIndex[colorIndex] == 0 || lastColorIndex[j] < position && lastColorIndex[j] > lastColorIndex[colorIndex]) {
                strokes[i] = strokes[i-1] + 1;
                hit = true;
                break;
            }
        }
        if (!hit) strokes[i] = strokes[i-1];
        lastColorIndex[colorIndex] = position;
    }

    vi lastColorIndexReverse(numColors);
    vi strokesReverse(inputs.size());

    strokesReverse[inputs.size() - 1] = 1;
    lastColorIndexReverse[inputs[inputs.size() - 1] - 'A'] = inputs.size();
    for (int i = inputs.size() - 2; i >= 0; i--) {
        int position = i+1;
        int colorIndex = inputs[i] - 'A';
        bool hit = false;
        if (colorIndex == 0 && lastColorIndexReverse[colorIndex] == 0) {
            strokesReverse[i] = strokesReverse[i+1] + 1;
            hit = true;
        }
        FOR(j, 0, colorIndex) {
            if (lastColorIndexReverse[colorIndex] == 0 || lastColorIndexReverse[j] > position && lastColorIndexReverse[j] < lastColorIndexReverse[colorIndex]) {
                strokesReverse[i] = strokesReverse[i+1] + 1;
                hit = true;
                break;
            }
        }
        if (!hit) strokesReverse[i] = strokesReverse[i+1];
        lastColorIndexReverse[colorIndex] = position;
    }

    FOR(i, 0, Q) {
        int result = 0;
        int start = ranges[i].first;
        int end = ranges[i].second;
        if (start != 1)
            result += strokes[start - 2];
        if (end < inputs.size())
            result += strokesReverse[end];
        cout << result << endl;
    }
    return 0;
}