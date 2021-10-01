#include <bits/stdc++.h>
#include <math.h>

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

vvi factors(3, vi(3));

struct MyHash {
    size_t operator()(const vvi& game) const {
        int ret = 0;
        FOR(i, 0, game.size()) {
            FOR(j,0,game[0].size()) {
                ret += game[i][j] * factors[i][j];
            }
        }
        return ret;
    }
};

unordered_set<vvi, MyHash> answer;
vi dx{-1, 0, 1, 0};
vi dy{0, -1, 0, 1};

bool check_win(vvi& game) {
    FOR(i,0,3) {
        if (game[i][0] == 2 && game[i][1] == 1 && game[i][2] == 1)
            return true;
        if (game[i][0] == 1 && game[i][1] == 1 && game[i][2] == 2)
            return true;
        if (game[0][i] == 2 && game[1][i] == 1 && game[2][i] == 1)
            return true;
        if (game[0][i] == 1 && game[1][i] == 1 && game[2][i] == 2)
            return true;
    }

    if (game[0][0] == 2 && game[1][1] == 1 && game[2][2] == 1)
        return true;
    if (game[0][0] == 1 && game[1][1] == 1 && game[2][2] == 2)
        return true;

    if (game[0][2] == 2 && game[1][1] == 1 && game[2][0] == 1)
        return true;
    if (game[0][2] == 1 && game[1][1] == 1 && game[2][0] == 2)
        return true;
    
    return false;
}

void find(int x, int y, vector<vvc>& inputs, vector<vector<unordered_set<vvi, MyHash>>>& visited, vvi game, int N) {
    if (visited[x][y].find(game) != visited[x][y].end())
        return;
    
    visited[x][y].insert(game);

    if (check_win(game))
    {
        answer.insert(game);
        return;
    }

    FOR(i,0,4) {
            vvi newGame = game;
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX < 0 || newX >= N || newY < 0 || newY >= N)
                continue;
            int move = 0;
            if (inputs[newX][newY][0] == 'M')
                move = 2;
            else if (inputs[newX][newY][0] == 'O')
                move = 1;
            else if (inputs[newX][newY][0] == '#')
                continue;
            int gameX = 0, gameY = 0;
            if (move == 1 || move == 2)
            {
                gameX = inputs[newX][newY][1] - '1';
                gameY = inputs[newX][newY][2] - '1';
                if (newGame[gameX][gameY] == 0) {
                    newGame[gameX][gameY] = move;
                    /*
                    if (check_win(newGame)) {
                        answer.insert(newGame);
                        continue;
                    }
                    */
                }
            }
            find(newX, newY, inputs, visited, newGame, N);
        }

    return;
}

int main() {
    int factor = 1;
    FOR(i,0,factors.size())
        FOR(j,0,factors[0].size()) {
            factors[i][j] = factor;
            factor *= 3;
        }

    int N;
    cin >> N;
    vector<vvc> inputs(N, vvc(N, vc(3)));
    int startX = 0;
    int startY = 0;
    FOR(i,0,N)
        FOR(j,0,N)
            FOR(k,0,3) {
                cin >> inputs[i][j][k];
                if (inputs[i][j][k] == 'B') {
                    startX = i;
                    startY = j;
                }
            }
    
    vector<vector<unordered_set<vvi, MyHash>>> visited(N, vector<unordered_set<vvi, MyHash>>(N));
    vvi game(3, vi(3));
    find(startX, startY, inputs, visited, game, N);

    cout << answer.size() << endl;

    return 0;
}