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

#define __SUBMIT

#ifndef __SUBMIT
    ifstream fIn("1.in");
    ofstream fOut("1.out");
    #define cin fIn
    #define cout fOut
#endif

const int maxCells = 1001;

vi dx = {0, 1, 0, -1};
vi dy = {1, 0, -1, 0};

int main() {
    int N;
    cin >> N;
    int result = 0;
    vvi edges(3*maxCells, vi(3*maxCells, -1));

    FOR(i, 0, N) {
        int x, y;
        cin >> x >> y;
        x += maxCells;
        y += maxCells;
        stack<pii> s;
        s.push(make_pair(x, y));
    
        
        while (!s.empty()) {
            pii cur = s.top();
            s.pop();
            x = cur.first;
            y = cur.second;
            if (edges[x][y] != -1) {
                result -= 1;
                continue;
            }
            edges[x][y] += 1;
            FOR(i, 0, 4) {
                int curX = x+dx[i];
                int curY = y+dy[i];
                if (edges[curX][curY] != -1) {
                    edges[curX][curY] += 1;
                    if (edges[curX][curY] == 3) {
                        FOR(j, 0, 4) {
                            if (edges[curX+dx[j]][curY+dy[j]] == -1) {
                                s.push(make_pair(curX+dx[j], curY+dy[j]));
                                result += 1;
                            }
                        }
                    }
                    edges[x][y] += 1;
                }
            }
            if (edges[x][y] == 3) {
                FOR(i, 0, 4) {
                    if (edges[x+dx[i]][y+dy[i]] == -1) {
                        s.push(make_pair(x+dx[i], y+dy[i]));
                        result += 1;
                    }
                }
            }
        }

        cout << result << endl;
    }
    return 0;
}