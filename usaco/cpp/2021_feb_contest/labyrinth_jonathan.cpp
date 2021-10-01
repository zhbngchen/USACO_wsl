#include "bits/stdc++.h"
using namespace std;

typedef long long ll; 
typedef pair<int, int> pii; 
typedef pair<ll, ll> pll; 
typedef pair<string, string> pss; 
typedef vector<int> vi; 
typedef vector<pii> vpi; 
typedef vector<vi> vvi;  
typedef vector<ll> vl; 
typedef vector<vl> vvl;
typedef set<int> si; 
typedef map<string, int> msi;
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

// Uncomment this line when submit / comment this line when test locally
#define __SUBMIT 

#ifndef __SUBMIT
    ifstream fin("in");
    ofstream fout("out");
    #define cin fin
    #define cout fout
#endif

struct point{
    int x;
    int y;
    point* parent;
    point(int a, int b, point* c = nullptr){
        x = a;
        y = b;
        parent = c;
    }
};

int n, m;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};
point* bfs_rec(vector<vector<char> >& grid, vector<point*>& layer, char cSrc, char cDest)
{
    vector<point*> newLayer;
    FOR(i, 0, layer.size()){
        int x = layer[i]->x;
        int y = layer[i]->y;
        if (x < 0 || x > n - 1) continue;
        if (y < 0 || y > m - 1) continue;
        if (grid[x][y] == 'B') return layer[i];
        if (grid[x][y] != cSrc) continue;
        grid[x][y] = cDest;
        for (int e = 0; e < sizeof(dx)/sizeof(int); ++e)
        {
            newLayer.push_back(new point(x+dx[e], y+dy[e], layer[i]));
        }
    }
    if(newLayer.size() == 0) return nullptr;
    return bfs_rec(grid, newLayer, cSrc, cDest);
}

vector<vector<char> > maze;
int ax, ay;
int main(){
    cin >> n >> m;
    maze.resize(n);
    FOR(x, 0, n){
        maze[x].resize(m);
        FOR(y, 0, m){
            cin >> maze[x][y];
            if(maze[x][y] == 'A'){
                ax = x;
                ay = y;
                maze[x][y] = '.';
            }
        }
    }
    vector<point*> layer0;
    layer0.push_back(new point(ax, ay));
    point* cur_pt = bfs_rec(maze, layer0, '.', '#');
    if(cur_pt == nullptr){
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    vector<char> path;
    while(cur_pt->parent != nullptr){
        if(cur_pt->parent->x > cur_pt->x) path.push_back('U');
        else if(cur_pt->parent->x < cur_pt->x) path.push_back('D');
        else if(cur_pt->parent->y > cur_pt->y) path.push_back('L');
        else if(cur_pt->parent->y < cur_pt->y) path.push_back('R');
        cur_pt = cur_pt->parent;
    }

    cout << path.size();
    cout << "\n";

    for(int i = path.size()-1; i >= 0; i--){
        cout << path[i];
    }

    return 0;
}
