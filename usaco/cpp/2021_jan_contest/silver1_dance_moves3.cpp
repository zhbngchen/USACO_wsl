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

bool cmp(int n, pair<int, int> const& p)
{
    // For instance...
    return n < p.first;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<vpii> cowsMoves(N+1);
    vpii moves(K);
    FOR(i, 0, K) {
        int a, b;
        cin >> a >> b;
        moves[i].first = a;
        moves[i].second = b;
        cowsMoves[a].push_back(make_pair(i,b));
        cowsMoves[b].push_back(make_pair(i, a));
    }

    FOR(i, 1, N+1) {
        if (cowsMoves[i].empty()) {
            cout << 1 << endl;
            continue;
        }
        vi moveStatus(K);
        vb visited(N+1);
        visited[i] = true;
        int result = 2;
        int moveIndex = cowsMoves[i][0].first;
        int next = cowsMoves[i][0].second;
        moveStatus[moveIndex] = next;
        visited[next] = true;
        while (true) {
            auto it = upper_bound(cowsLast[next], cowsMoves[next].end(), moveIndex, cmp);
            //if (it == cowsMoves[next].end())
            //    it = upper_bound(cowsMoves[next].begin(), cowsMoves[next].end(), moveIndex, cmp);
            if (it == cowsMoves[next].end())
                it = cowsMoves[next].begin();
            cowsLast[next] = it;
            moveIndex = it->first;
            next = it->second;
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