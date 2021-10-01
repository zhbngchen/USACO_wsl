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
    int N, Q;
    cin >> N >> Q;
    string colors;
    cin >> colors;
    vpii ranges(Q);
    FOR(i,0,Q)
        cin >> ranges[i].first >> ranges[i].second;
    
    map<int, vi> colorPos;
    FOR(i,0,colors.size()) {
        int index = colors[i] - 'A';
        
        colorPos[index].push_back(i+1);
    }

    FOR(i,0,Q) {
        int result = 0;
        int start = ranges[i].first;
        int end = ranges[i].second;
        for (auto it = colorPos.begin(); it != colorPos.end(); it ++) {
            auto it2 = lower_bound(it->second.begin(), it->second.end(), start);
            if (it2 != it->second.begin())
                result ++;
            it2 = upper_bound(it->second.begin(), it->second.end(), end);
            if (it2 != it->second.end())
                result ++;
        }
        cout << result << endl;
    }
    return 0;
}