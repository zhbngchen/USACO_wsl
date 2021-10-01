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

//#define __SUBMIT

#ifndef __SUBMIT
    ifstream fIn("1.in");
    ofstream fOut("1.out");
    #define cin fIn
    #define cout fOut
#endif

struct TicTacMove {
    char move;
    int x;
    int y;
    TicTacMove(char m, int i, int j) : move(m), x(i), y(j) {}
};

void addMove(vvc& game, TicTacMove move) {
    if (game[move.x][move.y] == '.')
        game[move.x][move.y] = move.move;
}
vector<vvc> gen_combo(vector<TicTacMove> moves, int ind) {
    vector<vvc> ret;
    vvc game(3, vc(3, '.'));
    if (ind != -1) {
        addMove(game, moves[ind]);
        ret.push_back(game);
    }
    FOR(i,0,moves.size()) { // size 2
        vvc game2(game);
        if (i != ind) {
            addMove(game2, moves[i]);
            ret.push_back(game2);
        }
    }
    FOR(i,0,moves.size()) { // size 3
        vvc game2(game);
        if (i == ind)
            continue;
        addMove(game2, moves[i]);
        FOR(j,0,moves.size()) {
            vvc game3(game2); 
            if (j == ind || j == i)
                continue;
            addMove(game3, moves[j]);
            ret.push_back(game3);
        }
    }
    FOR(i,0,moves.size()) { // size 4
        vvc game2(game);
        if (i == ind)
            continue;
        addMove(game2, moves[i]);
        FOR(j,0,moves.size()) {
            vvc game3(game2); 
            if (j == ind || j == i)
                continue;
            addMove(game3, moves[j]);
            game3[moves[j].x][moves[j].y] = moves[j].move;
            FOR(k,0,moves.size()) {
                vvc game4(game3);
                if (k == ind || k == i || k == j)
                    continue;
                addMove(game4, moves[k]);
                ret.push_back(game3);
            }
        }
    }
    return ret;
}

bool check_win(int val) {
    int mask = 3;

    // horizontal
    FOR(i,0,3)
        if (((val >> (i*6)) & mask) == 1 && ((val >> (i*6 + 2)) & mask == 2) && ((val >> (i*6 + 4)) & mask == 2) ||
            ((val >> (i*6)) & mask) == 2 && ((val >> (i*6 + 2)) & mask == 2) && ((val >> (i*6 + 4)) & mask == 1))
            return true;

    // vertical
    FOR(j,0,3)
        if (((val >> (j*2)) & mask) == 1 && ((val >> (j*2 + 6)) & mask == 2) && ((val >> (j*2 + 12)) & mask == 2) ||
            ((val >> (j*2)) & mask) == 2 && ((val >> (j*2 + 6)) & mask == 2) && ((val >> (j*2 + 12)) & mask == 1))
            return true;

    // diagonal
    FOR(i,0,3)
        if (((val & mask) == 1 && ((val >> (6 + 2)) & mask == 2) && ((val >> (12 + 4)) & mask == 2)) ||
            ((val & mask) == 2 && ((val >> (6 + 2)) & mask == 2) && ((val >> (12 + 4)) & mask == 1)))
            return true;
    return false;
}

int main() 
{
    int N;
    cin >> N;
    vvc inputs(N, vc(N*3));
    FOR(i,0,N)
        FOR(j,0,3*N)
            cin >> inputs[i][j];
    
    vi dx({-1, 0, 1, 0});
    vi dy({0, -1, 0, 1});
    si results;
    FOR(i,0,N)
        FOR(j,0,N) {
            vvb visited(N, vb(N));
            vvi inQeueuCounts(N, vi(N));
            if (inputs[i][j*3] == 'B') {
                vector<vector<vvc>> accumulatedCombos(N, vector<vvc>(N, vvc(3, vc(3, '.'))));
                queue<pii> q;
                q.push(make_pair(i,j));
                inQeueuCounts[i][j] = 1;
                while(!q.empty()) {
                    pii cur = q.front();
                    q.pop();
                    int x = cur.first, y = cur.second;
                    if (--inQeueuCounts[x][y] == 0)
                        visited[x][y] = true;
                    vector<TicTacMove> moves;
                    FOR(k,0,4) {
                        x = cur.first + dx[k];
                        y = cur.second + dy[k];
                        if (visited[x][y]) {
                            continue;
                        }
                        char move = inputs[x][y*3];
                        int tic_tac_cordX = 0, tic_tac_cordY = 0;
                        if (move == 'M' || move == 'O') {
                            tic_tac_cordX = inputs[x][y*3+1] - '1';
                            tic_tac_cordY = inputs[x][y*3+2] - '1';
                        }
                        else {
                            continue;
                        }
                        
                        moves.push_back(TicTacMove(move, tic_tac_cordX, tic_tac_cordY));
                    }
                    int ind = 0;
                    FOR(k,0,4) {
                        x = cur.first + dx[k];
                        y = cur.second + dy[k];
                        if (visited[x][y])
                            continue;
                        char move = inputs[x][y*3];
                        if (move == 'M' || move == 'O' || move == '.') {
                            int index = 0;
                            if (move == '.')
                                index = -1;
                            else
                                index = ind++;
                            vector<vvc> combos = gen_combo(moves, index);
 
                            if (accumulatedCombos[cur.first][cur.second].empty())
                                accumulatedCombos[cur.first][cur.second] = combos;
                            if (accumulatedCombos[x][y].empty())
                                accumulatedCombos[x][y] = accumulatedCombos[cur.first][cur.second];
                            for (auto val1 : accumulatedCombos[x][y])
                                for (auto val2 : combos)
                                    accumulatedCombos[x][y].insert(val1 + val2);
                            for (auto val : accumulatedCombos[x][y])
                            {
                                if (check_win(val))
                                {
                                    accumulatedCombos[x][y].erase(val);
                                    results.insert(val);
                                }
                            }
                            q.push(make_pair(x, y));
                            inQeueuCounts[x][y]++;
                        }
                    }
                }
            }
        }

    cout << results.size() << endl;

    return 0;
}