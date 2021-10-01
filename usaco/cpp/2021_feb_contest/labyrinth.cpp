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

typedef vector<char> vc;
typedef vector<vc> vvc;

typedef vector<vb> vvb;

typedef vector<string> vs;
typedef vector<vs> vvs;

typedef vector<pii> vpii;
typedef vector<char> vc;

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;


#ifdef __LOCAL
    ifstream fIn("in");
    ofstream fOut("out");
    #define cin fIn
    #define cout fOut
#endif

int main() {
    int n, m;
    cin >> n >> m;
    vvc grid(n, vc(m));
    FOR(i,0,n)
        FOR(j,0,m)
            cin >> grid[i][j];

    vi dx = {-1, 0, 1, 0};
    vi dy = {0, -1, 0, 1};
    vc directions = {'U', 'L', 'D', 'R'};
    map<char, pii> dir2move = { {'U', pii(1, 0)}, {'L', pii(0, 1)}, {'D', pii(-1, 0)}, {'R', pii(0, -1)}};

    vvb visited(n, vb(m));
    vvc paths(n, vc(m));
    vvi pathCounts(n, vi(m));
    FOR(i,0,n)
        FOR(j,0,n) {
            if (grid[i][j] == 'A') {
                queue<pii> q;
                q.push(make_pair(i, j));
                visited[i][j] = true;
                while (!q.empty()) {
                    pii cords = q.front();
                    q.pop();
                    int x = cords.first, y = cords.second;
                    if (grid[x][y] == 'B') {
                        cout << "YES" << endl;
                        cout << pathCounts[x][y] << endl;
                        string result;
                        while (grid[x][y] != 'A') {
                            result += paths[x][y];
                            char dir = paths[x][y];
                            x += dir2move[dir].first;
                            y += dir2move[dir].second;
                        }
                        reverse(result.begin(), result.end());
                        cout << result << endl;
                        return 0;
                    }
                    FOR(k, 0, 4)
                    {
                        int newX = x + dx[k], newY = y + dy[k];
                        if (newX >= 0 && newX < n && newY >= 0 && newY < m && 
                            !visited[newX][newY] && grid[newX][newY] != '#')
                        {
                            paths[newX][newY] = directions[k];
                            pathCounts[newX][newY] = pathCounts[x][y] + 1;
                            q.push(make_pair(newX, newY));
                            visited[newX][newY] = true;
                        }
                    }
                }
            }
        }
    cout << "NO" << endl;
    return 0;
}