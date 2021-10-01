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
 
struct City {
    int id;
    int from;
    int depth;
    City(int i, int f, int d) : id(i), from(f), depth(d) {}
};
 
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
            stack<City> s;
            s.push(City(i, -1, 1));
            visited[i] = true;
            while (!s.empty())
            {
                City curCity = s.top();
                s.pop();
                int cur = curCity.id;
                int depth = curCity.depth;
                if (path.size() >= depth)
                {
                    int popN = path.size() - depth + 1;
                    FOR(j, 0, popN)
                        path.pop_back();
                }
                path.push_back(cur);
                visited[cur] = true;
                bool hasPush = false;
                for (auto n : neighbors[cur])
                {
                    if (n != curCity.from)
                    {
                        if (!visited[n]) {
                            s.push(City(n, cur, depth + 1));
                            hasPush = true;
                        }
                        else
                        {
                            path.push_back(n);
                            int j = 0;
                            while (path[j] != n) j++;
                            cout << path.size() - j << endl;
                            for (int k = j; k < path.size(); k++)
                                cout << path[k] << " ";
                            cout << endl;
                            return 0;
                        }
                    }
                }
                /*
                if (!hasPush) {
                    path.pop_back();
                }*/
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
 
    return 0;
}