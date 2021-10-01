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

int checkPaint(vvi& colorPos, int cur, vi::iterator first, vi::iterator last) {
    int result = 1;

    for (vi::iterator it = first; it != last; it++) {
        vi::iterator next = it + 1;
        if (next != last) {
            FOR(i, 0, cur) {
                vi::iterator it2 = upper_bound(colorPos[i].begin(), colorPos[i].end(), *it);
                if (it2 != colorPos[i].end() && *it2 < *next) { 
                    result ++;
                    break;
                }
            }
        }
    }
    return result;
}

int main() {
    int N, Q;
    cin >> N >> Q;
    string colors;
    cin >> colors;
    vpii ranges(Q);
    FOR(i,0,Q)
        cin >> ranges[i].first >> ranges[i].second;
    
    vvi colorPos(26);
    FOR(i,0,colors.size()) {
        int index = colors[i] - 'A';
        
        colorPos[index].push_back(i+1);
    }

    FOR(i,0,Q) {
        int result = 0;
        int start = ranges[i].first;
        int end = ranges[i].second;
        FOR(j, 0, colorPos.size()) {
            vi::iterator it2 = lower_bound(colorPos[j].begin(), colorPos[j].end(), start);
            if (it2 != colorPos[j].begin())
                result += checkPaint(colorPos, j, colorPos[j].begin(), it2);
            it2 = upper_bound(colorPos[j].begin(), colorPos[j].end(), end);
            if (it2 != colorPos[j].end())
                result += checkPaint(colorPos, j, it2, colorPos[j].end());
        }
        cout << result << endl;
    }

    return 0;
}