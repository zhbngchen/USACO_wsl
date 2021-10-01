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

int main() {
    int N;
    cin >> N;
    vvi blockers(N+1, vi(N+1));
    vvi optimals(N+1, vi(N+1));
    FOR(i,1,N+1) {
        FOR(j,1,N+1) {
            int val;
            cin >> val;
            if (val == 100) {
                blockers[i][j] = 1;
            }
            else if (val > 100) {
                optimals[i][j] = 1;
                blockers[i][j] = 1;
            }
            else { // val < 100
                optimals[i][j] = 1;
            }
        }
    }

    // 2D roll
    FOR(i,0,N+1) {
        FOR(j,0,N) {
            blockers[i][j+1] = blockers[i][j] + blockers[i][j+1];
            optimals[i][j+1] = optimals[i][j] + optimals[i][j+1];
        }
    }
    FOR(i,0,N) {
        FOR(j,0,N+1) {
            blockers[i+1][j] += blockers[i][j];
            optimals[i+1][j] += optimals[i][j];
        }
    }

    long long result = 0;
    FOR(i, 1, N+1) {
        FOR(j, 1, N+1) {
            FOR(k, i, N+1) {
                FOR(l, j, N+1) {
                    if (blockers[k][l] - blockers[k][j-1] - blockers[i-1][l] + blockers[i-1][j-1] == (k - i + 1) * (l - j + 1) && 
                        optimals[k][l] - optimals[k][j-1] - optimals[i-1][l] + optimals[i-1][j-1] != (k - i + 1) * (l - j + 1)) {
                            result += 1;
                    }
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}