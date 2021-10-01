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
    vi inputs(N);
    FOR(i, 0, N)
        cin >> inputs[i];

    int odd = 0;
    int even = 0;
    FOR(i, 0, N) {
        if (inputs[i] % 2 == 0)
            even ++;
        else
            odd ++;
    }
    int result = min(odd, even) * 2;
    int left = max(odd, even) - min(odd, even);
    if (even > odd) result ++;
    else {
        result += (left/3)*2;
        left %= 3;
        if (left == 1) result --;
        else if (left == 2) result ++;
    }

    cout << result << endl;

    return 0;
}