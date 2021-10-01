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

    vpii moves(K);
    FOR(i, 0, K) {
        int a, b;
        cin >> a >> b;
        moves[i].first = a;
        moves[i].second = b;
    }

    vvi cowLocations(N+1);
    vi cows(N+1);
    FOR(i, 0, N+1) {
        cows[i] = i;
        cowLocations[i].push_back(i);
    }

    FOR(i, 0, K) {
        int x = moves[i].first;
        int y = moves[i].second;
        cowLocations[cows[x]].push_back(y);
        cowLocations[cows[y]].push_back(x);
        swap(cows[x], cows[y]);
    }

    vi results(N+1);
    vb visited(N+1);
    FOR(i, 1, N+1) {
        if (!visited[i]) {
            int count=0;
            vb countVisited(N+1);
            set<int> cowsSet;
            stack<int> s;
            s.push(i);
            while(!s.empty()) {
                int t = s.top();
                s.pop();
                visited[t] = true;
                cowsSet.insert(t);
                FOR(j, 0, cowLocations[t].size()) {
                    int cowPosition = cowLocations[t][j];
                    if (!countVisited[cowPosition]) {
                        countVisited[cowPosition] = true;
                        count++;
                    }
                }
                int end = cowLocations[t][cowLocations[t].size() - 1];
                if (!visited[end]) {
                    s.push(end);
                }
            }
            for (auto it = cowsSet.begin(); it != cowsSet.end(); it++)
                results[*it] = count;
        }
    }

    FOR(i, 1, N+1)
        cout << results[i] << endl;

    return 0;
}