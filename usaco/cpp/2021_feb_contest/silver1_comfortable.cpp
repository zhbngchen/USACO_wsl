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

enum CowStatus {
    EMPTY = 0,
    INPUT = 1,
    CREATED = 2
};

struct CellStatus {
    CowStatus status;
    int edgeCount;
};

const int maxCells = 1001;

vector<vector<CellStatus>> cells(3*maxCells, vector<CellStatus>(3*maxCells));

vi dx = {0, 1, 0, -1};
vi dy = {1, 0, -1, 0};

int checkNeighbors(int x, int y);

int fillCreated(int x, int y) {
    int ret = 0;
    FOR(i, 0, 4) {
        if (cells[x+dx[i]][y+dy[i]].status == EMPTY) {
            cells[x+dx[i]][y+dy[i]].status = CREATED;
            ret += checkNeighbors(x+dx[i], y+dy[i]);
            break;
        }
    }
    return ret;
}

int checkNeighbors(int x, int y) {
    int ret = 0;
    FOR(i, 0, 4) {
        if (cells[x+dx[i]][y+dy[i]].status == INPUT || cells[x+dx[i]][y+dy[i]].status == CREATED) {
                cells[x+dx[i]][y+dy[i]].edgeCount += 1;
                if (cells[x+dx[i]][y+dy[i]].edgeCount == 3) {
                    ret += fillCreated(x+dx[i], y+dy[i]);
                    ret += 1;
                }
                cells[x][y].edgeCount += 1;
            }
    }
    if (cells[x][y].edgeCount == 3)
    {
        ret += fillCreated(x, y);
        ret += 1;
    }

    return ret;
}

int main() {
    int N;
    cin >> N;
    int additionalCows = 0;
    FOR(i, 0, N) {
        int x, y;
        cin >> x >> y;
        x += maxCells;
        y += maxCells;
        if (cells[x][y].status == CREATED) {
            additionalCows -= 1;
            cells[x][y].status = INPUT;
        }
        else {
            cells[x][y].status = INPUT;
            additionalCows += checkNeighbors(x, y);
        }
        cout << additionalCows << endl;
    }
    return 0;
}