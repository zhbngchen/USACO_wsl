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

int N;

vpii inputCordX;
vpii inputCordY;

struct Cow {
    int x;
    int y;
    char dir;
    int indexX;
    int indexY;
};

vector<Cow> cows;

Graph stopRelations;
vi stopped;

void checkBlocked(int cowIndex, int step) {
    if (cows[cowIndex].dir == 'N') {
        int next = cows[cowIndex].y + step;
        FOR(i, cows[cowIndex].indexY, N) {
            int againstIndex = inputCordY[i].second;
            int againstY = cows[againstIndex].y;
            if (cows[againstIndex].dir == 'N' || 
                next > againstY || 
                (stopped[againstIndex] && cows[cowIndex].x >= stopped[againstIndex]))
                continue;
            else if (next == againstY) {
                if (cows[againstIndex].x < cows[cowIndex].x && cows[againstIndex].x + step > cows[cowIndex].x) {
                    stopped[cowIndex] = inputCordY[i].first;
                    stopRelations[againstIndex].push_back(cowIndex);
                    return;
                }
            }
            else {
                cows[cowIndex].indexY = i;
                return;
            }
        }
    }
    else { // 'E'
        int next = cows[cowIndex].x + step;
        FOR(i, cows[cowIndex].indexX, N) {
            int againstIndex = inputCordX[i].second;
            int againstX = cows[againstIndex].x;
            if (cows[againstIndex].dir == 'E' ||
                next > againstX || 
                (stopped[againstIndex] && cows[cowIndex].y >= stopped[againstIndex]))
                continue;
            else if (next == againstX) {
                if (cows[againstIndex].y < cows[cowIndex].y && cows[againstIndex].y + step > cows[cowIndex].y) {
                    stopped[cowIndex] = inputCordX[i].first;
                    stopRelations[againstIndex].push_back(cowIndex);
                    return;
                }
            }
            else {
                cows[cowIndex].indexX = i;
                return;
            }
        }
    }
}

int main() {

#define __SUBMIT

#ifdef __SUBMIT
    #define fIn cin
    #define fOut cout
#else
    ifstream fIn("1.in");
    ofstream fOut("1.out");
#endif

    fIn >> N;
    stopped.resize(N);
    cows.resize(N);
    FOR(i, 0, N) {
        fIn >> cows[i].dir;
        fIn >> cows[i].x >> cows[i].y;
        inputCordX.push_back(make_pair(cows[i].x, i));
        inputCordY.push_back(make_pair(cows[i].y, i));
    }
    sort(inputCordX.begin(), inputCordX.end());
    sort(inputCordY.begin(), inputCordY.end());

    set<int> steps;
    FOR(i, 0, N)
        FOR(j, i+1, N) {
            steps.insert(inputCordX[j].first - inputCordX[i].first);
            steps.insert(inputCordY[j].first - inputCordY[i].first);
        }

    //cout << "steps size: " << steps.size() << endl;

    bool done = false;
    int time = 0;
    for (auto step: steps)
        FOR(i, 0, N)
            if (!stopped[i])
                checkBlocked(i, step);
    
    // For each stopRelations, find counts
    vi results(N);
    for (auto it = stopRelations.begin(); it != stopRelations.end(); it ++) {
        queue<int> q;
        for (auto s: it->second)
            q.push(s);
        while (!q.empty()) {
            int f = q.front();
            q.pop();
            results[it->first] += 1;
            for (auto s2: stopRelations[f])
                q.push(s2);
        }
    }
    // output
    FOR(i, 0, N)
        fOut << results[i] << endl;

    return 0;
}