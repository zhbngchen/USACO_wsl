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

#ifdef __SUBMIT
    #define fIn cin
    #define fOut cout
#else
    ifstream fIn("1.in");
    ofstream fOut("1.out");
#endif

int N;
struct Cow {
    int x;
    int y;
};

vector<Cow> cows;
vpii xN; // pair with north moving cow's x and index to cows
vpii yE; // pair with east moving cow's y and index to cows

Graph stopRelations;

int main() {
    fIn >> N;
    cows.resize(N);
    FOR(i, 0, N) {
        char c;
        int x, y;
        fIn >> c >> x >> y;
        if (c == 'N')
            xN.push_back(make_pair(x, i));
        else // 'E'
            yE.push_back(make_pair(y, i));
        cows[i].x = x;
        cows[i].y = y;
    }
    sort(xN.begin(), xN.end());
    sort(yE.begin(), yE.end());

    vb stopped(N);
    FOR(i, 0, xN.size())
        FOR(j, 0, yE.size()) {
            int nIndex = xN[i].second;
            int eIndex = yE[j].second;
            int xE = cows[eIndex].x, yE = cows[eIndex].y, xN = cows[nIndex].x, yN = cows[nIndex].y;
            if (!stopped[nIndex] && !stopped[eIndex] && xE < xN && yE > yN) {
                int eDistance = xN - xE;
                int nDistance = yE - yN;
                if (eDistance > nDistance) {
                    stopRelations[nIndex].push_back(eIndex);
                    stopped[eIndex] = true;
                }
                else if (eDistance < nDistance) {
                    stopRelations[eIndex].push_back(nIndex);
                    stopped[nIndex] = true;
                }
            }
        }

    // For each stopRelations, find counts
    vi results(N);
    for (auto it = stopRelations.begin(); it != stopRelations.end(); it ++) {
        stack<int> stk;
        for (auto s: it->second)
            stk.push(s);
        while (!stk.empty()) {
            int f = stk.top();
            stk.pop();
            results[it->first] += 1;
            for (auto s2: stopRelations[f])
                stk.push(s2);
        }
    }
    // output
    FOR(i, 0, N)
        fOut << results[i] << endl;
    return 0;
}