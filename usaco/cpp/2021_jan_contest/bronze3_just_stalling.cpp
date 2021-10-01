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
    vi cows(N);
    vi stalls(N);
    FOR(i,0,N)
        cin >> cows[i];
    FOR(i,0,N)
        cin >> stalls[i];
    long long result = 1;

    sort(cows.begin(), cows.end());
    sort(stalls.begin(), stalls.end());

    int indCows=0, indStalls=0;
    while(indStalls < stalls.size()) {
        while(indCows < cows.size() && cows[indCows] <= stalls[indStalls])
            indCows++;
        result *= (indCows - indStalls);
        indStalls ++;
    }
    cout << result << endl;
    return 0;
}