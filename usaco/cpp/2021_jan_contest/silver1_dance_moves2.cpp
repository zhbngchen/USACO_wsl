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

const int INIT = 0;
const int ALLDONE = -1;

int main() {
    int N, K;
    cin >> N >> K;

    vvi cowsMoveIndex(N+1);
    vvi cowsMoveNext(N+1);
    vpii moves(K);
    FOR(i, 0, K) {
        int a, b;
        cin >> a >> b;
        moves[i].first = a;
        moves[i].second = b;
        cowsMoveIndex[a].push_back(i);
        cowsMoveNext[a].push_back(b);
        cowsMoveIndex[b].push_back(i);
        cowsMoveNext[b].push_back(a);
    }

    FOR(i, 1, N+1) {
        if (cowsMoveIndex[i].empty()) {
            cout << 1 << endl;
            continue;
        }
        vi moveStatus(K);
        vb visited(N+1);
        visited[i] = true;
        int result = 2;
        int moveIndex = cowsMoveIndex[i][0];
        int next = cowsMoveNext[i][0];
        moveStatus[moveIndex] = next;
        visited[next] = true;
        while (true) {
            auto it = upper_bound(cowsMoveIndex[next].begin(), cowsMoveIndex[next].end(), moveIndex);
            if (it == cowsMoveIndex[next].end())
                it = cowsMoveIndex[next].begin();
            moveIndex = *it;
            next = cowsMoveNext[next][it - cowsMoveIndex[next].begin()];
             if (moveStatus[moveIndex] == ALLDONE || moveStatus[moveIndex] == next)
                break;
            else {
                if (!visited[next]) {
                    visited[next] = true;
                    result += 1;
                }
                if (moveStatus[moveIndex] == INIT)
                    moveStatus[moveIndex] = next;
                else
                    moveStatus[moveIndex] = ALLDONE;
            }
        }
        cout << result << endl;
    }
    
    return 0;
}