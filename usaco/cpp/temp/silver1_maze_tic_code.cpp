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

const int BASE = 4;

struct Move {
    int val;
    int x;
    int y;
    Move(): val(0), x(0), y(0) {}
    Move(int v, int x1, int y1): val(v), x(x1), y(y1) {}
};

vvi factors(3, vi(3));

unordered_set<int> answer;

vi dx{-1, 0, 1, 0};
vi dy{0, -1, 0, 1};

bool check_win(int gameCode) {
    vvi game(3, vi(3));
    int mask = 3;
    FOR(i,0,3)
        FOR(j,0,3) {
            game[i][j] = gameCode & mask;
            gameCode >>= 2;
        }

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

int genCode(int code, Move& move) {
    int val = move.val;
    if (val != 2 && val != 1)
        return code;
    int x = move.x, y = move.y;
    int currentState = (int)(code / factors[x][y]) % BASE;
    if (currentState == 0) {
        code += move.val * factors[x][y];
    }
    return code;
}

void find(int x, int y, vector<vector<Move>>& inputs, vector<vector<vb>>& visited, int gameCode, int N) {
    if (visited[x][y][gameCode])
        return;
    
    visited[x][y][gameCode] = true;

    int newGameCode = genCode(gameCode, inputs[x][y]);
    if (!visited[x][y][newGameCode] && check_win(newGameCode))
    {
        //visited[x][y][newGameCode] = true;
        answer.insert(newGameCode);
        return;
    }
    //visited[x][y][newGameCode] = true;

    FOR(i,0,4) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX < 0 || newX >= N || newY < 0 || newY >= N)
                continue;
            if (inputs[newX][newY].val == -1) // '#'
                continue;
            find(newX, newY, inputs, visited, newGameCode, N);
        }

    return;
}

int main() {
    int factor = 1;
    FOR(i,0,factors.size())
        FOR(j,0,factors[0].size()) {
            factors[i][j] = factor;
            factor *= BASE;
        }

    int N;
    cin >> N;
    vector<vector<Move>> inputs(N, vector<Move>(N));
    int startX = 0;
    int startY = 0;
    FOR(i,0,N)
        FOR(j,0,N) {
            char v, x, y;
            cin >> v >> x >> y;
            switch (v) {
                case '#':
                    inputs[i][j].val = -1;
                    break;
                case '.':
                    inputs[i][j].val = 0;
                    break;
                case 'B':
                    inputs[i][j].val = 0;
                    startX = i;
                    startY = j;
                    break;
                case 'M':
                    inputs[i][j].val = 2;
                    inputs[i][j].x = x - '1';
                    inputs[i][j].y = y - '1';
                    break;
                case 'O':
                    inputs[i][j].val = 1;
                    inputs[i][j].x = x - '1';
                    inputs[i][j].y = y - '1';
                    break;
                default:
                    break;
            }
        }
    
    vector<vector<vb>> visited(N, vector<vb>(N, vb(pow(BASE, 9))));
    find(startX, startY, inputs, visited, 0, N);

    cout << answer.size() << endl;

    return 0;
}