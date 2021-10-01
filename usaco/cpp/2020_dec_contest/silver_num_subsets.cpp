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

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

vpii inputs;

#define __SUBMIT

#ifdef __SUBMIT
    #define fIn cin
    #define fOut cout
#else
    ifstream fIn("1.in");
    ofstream fOut("1.out");
#endif

bool compy(pii p1, pii p2) { return p1.second < p2.second; }

vvi psum;

int calcSum(int x1, int y1, int x2, int y2) {
  return psum[x2+1][y2+1] - psum[x1][y2+1] - psum[x2+1][y1] + psum[x1][y1];
}

int main() {
    int N;

    // read input
    cin >> N;
    inputs.resize(N);

    FOR(i, 0, N) {
        cin >> inputs[i].first >> inputs[i].second;
    }
    sort(inputs.begin(), inputs.end());
    FOR(i, 0, N)
      inputs[i].first = i+1;
    sort(inputs.begin(), inputs.end(), compy);
    FOR(i, 0, N)
      inputs[i].second = i+1;

    psum.resize(N+1, vi(N+1));
    FOR(i, 0, N)
      psum[inputs[i].first][inputs[i].second] = 1;
    
    FOR(i, 1, N+1)
      FOR(j, 1, N+1)
        psum[i][j] += psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];

    long long result = 0;
    FOR(i, 0, N)
      FOR(j, i, N) {
        int xMin = min(inputs[i].first, inputs[j].first) - 1;
        int xMax = max(inputs[i].first, inputs[j].first) - 1;
        int yMin = min(inputs[i].second, inputs[j].second) - 1; // should be i
        int yMax = max(inputs[i].second, inputs[j].second) - 1; // should be j
        result += calcSum(0, yMin/*i*/, xMin, yMax/*j*/) * calcSum(xMax, yMin/*i*/, N-1, yMax/*j*/);
      }
    cout << result + 1 << endl;

    return 0;
}
