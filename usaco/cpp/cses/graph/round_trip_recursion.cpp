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
typedef vector<vc> vvc;


using vsi = vector<unordered_set<int>>;
using vvb = vector<vector<bool>>;

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

#ifdef __LOCAL
    ifstream fIn("in");
    ofstream fOut("out");
    #define cin fIn
    #define cout fOut
#endif

bool find(int from, int cur, vi& path, vvi& neighbors, vb& visited) {
    for(int i = 0; i < neighbors[cur].size(); i++) {
        int next = neighbors[cur][i];
        if (next == from) continue;
        if (!visited[next]) {
            path.push_back(next);
            visited[next] = true;
            if(find(cur, next, path, neighbors, visited))
                return true;
            path.pop_back();
        }
        else
        {
            path.push_back(next);
            return true;
        }
        
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vvi neighbors(n+1);
    FOR(i,0,m) {
        int x, y;
        cin >> x >> y;
        neighbors[x].push_back(y);
        neighbors[y].push_back(x);
    }
    
    vb visited(n+1);
    FOR(i,1,n+1) {
        if (!visited[i]) {
            vi path;
            visited[i] = true;
            path.push_back(i);
            if (find(-1, i, path, neighbors, visited))
            {
                int last = path[path.size() - 1];
                int j = 0;
                while(path[j] != last) j++;
                cout << path.size() - j << endl;
                FOR(k,j,path.size())
                    cout << path[k] << " ";
                cout << endl;
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}