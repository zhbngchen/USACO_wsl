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

using vsi = vector<unordered_set<int>>;
using vvb = vector<vector<bool>>;

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

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int main() {
    int N, K;
    cin >> N >> K;
    vpii moves(K);
    FOR(i, 0, K)
        cin >> moves[i].first >> moves[i].second;
    
    vi cows(N+1);
    FOR(i,1,N+1)
        cows[i] = i;
    int i = 0;
    vvb cowPositions(N+1);
    FOR(i, 1, N+1) {
        cowPositions[i].resize(N+1);
        cowPositions[i][i] = true;
    }
    int outOrderCount = 0;
    vb outOrderCows(N+1);
    while(true) {
        int moveIndex1 = moves[i].first;
        int moveIndex2 = moves[i].second;
        swap(cows[moveIndex1], cows[moveIndex2]);
        int cowId1 = cows[moveIndex1];
        int cowId2 = cows[moveIndex2];
        if (!outOrderCows[cowId1] && cowId1 != moveIndex1) {
            outOrderCount++;
            outOrderCows[cowId1] = true;
        }
        if (!outOrderCows[cowId2] && cowId2 != moveIndex2) {
            outOrderCount++;
            outOrderCows[cowId2] = true;
        }
        if (outOrderCows[cowId1] && cowId1 == moveIndex1) {
            outOrderCount--;
            outOrderCows[cowId1] = false;
        }
        if (outOrderCows[cowId2] && cowId2 == moveIndex2) {
            outOrderCount--;
            outOrderCows[cowId2] = false;
        }
        if (outOrderCount == 0)
            break;
        cowPositions[cowId1][moveIndex1] = true;;
        cowPositions[cowId2][moveIndex2] = true;
        i++;
        if (i == moves.size())
            i = 0;
    }
    FOR(i, 1, N+1) {
        int result = 0;
        FOR(j, 1, N+1) {
            if (cowPositions[i][j])
                result ++;
        }
        cout << result << endl;
    }
    return 0;
}