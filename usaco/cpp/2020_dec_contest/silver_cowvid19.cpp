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

int main() {
    int N;
    Graph g;

    // read inputs
    cin >> N;
    FOR(k, 0, N-1) {
        int i, j;
        cin >> i >> j;
        g[i].push_back(j);
        g[j].push_back(i);
    }

    int result = 0;
    // DFS
    vb visited(N+1);
    stack<int> stackInt;
    stackInt.push(1);
    while(!stackInt.empty()) {
        int cur = stackInt.top();
        stackInt.pop();
        visited[cur] = true;
        int farmCount = 0;
        vector<pii> vpii;
        FOR(i, 0, g[cur].size()) {
            int next = g[cur][i];
            if (!visited[next]) {
                stackInt.push(next);
                farmCount += 1;
            }
        }
/*        FOR(i, 0, g[cur].size()) {
            int next = g[cur][i];
            if (visited[next])
                continue;
            int count = 1;
            FOR(j, 0, g[next].size()) {
                if (!visited[g[next][j]])
                    count += 1;
            }
            vpii.push_back(make_pair(count, next));
        }
        sort(vpii.begin(), vpii.end());
        FOR(i, 0, vpii.size()) {
            int next = vpii[i].second;
            stackInt.push(next);
            farmCount += 1;
        }*/
        int days = 0;
        int count = 1;
        while (count <= farmCount) {
            count <<= 1;
            days += 1;
        }
        result += days;
        result += farmCount;
    }

    // output
    cout << result << endl;

    return 0;
}