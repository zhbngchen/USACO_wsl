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

int main() 
{
    int N, K;
    cin >> N >> K;
    vpii cowMoves(K);
    FOR(i, 0, K)
        cin >> cowMoves[i].first >> cowMoves[i].second;
    
    vi cowPositions(N+1);
    vvi cowHasBeen(N+1);
    FOR(i, 0, N+1) {
        cowPositions[i] = i;
        cowHasBeen[i].push_back(i);
    }

    vi cowEndPosition(N+1);
    FOR(i, 0, K) {
        int cowSwapIndex1 = cowMoves[i].first;
        int cowSwapIndex2 = cowMoves[i].second;
        int cow1 = cowPositions[cowSwapIndex1];
        int cow2 = cowPositions[cowSwapIndex2];
        swap(cowPositions[cowSwapIndex1], cowPositions[cowSwapIndex2]);
        cowHasBeen[cow1].push_back(cowSwapIndex2);
        cowHasBeen[cow2].push_back(cowSwapIndex1);
    }
    FOR(i, 0, N+1)
        cowEndPosition[i] = cowHasBeen[i][cowHasBeen[i].size() - 1];
    
    // DFS on cowEndPosition to find groups, at the same time find the HasBeens for the group
    vb visited(N+1);
    int groupIndex = 0;
    FOR(i, 1, N+1) {
        stack<int> s;
        if (!visited[i]) {
            vb counted(N+1);
            vi hasBeen;
            hasBeen.push_back(i);
            s.push(i);
            while(!s.empty()) {
                int cur = s.top();
                s.pop();
                int next = cowEndPosition[cur];
                if (!visited[next]) {
                    s.push(next);
                }
            }
        }
    }
    return 0;
}