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


#ifdef __LOCAL
    ifstream fIn("in");
    ofstream fOut("out");
    #define cin fIn
    #define cout fOut
#endif

int main() {
    int n, x;
    cin >> n >> x;
    vi weights(n);
    FOR(i,0,n)
        cin >> weights[i];
    sort(weights.begin(), weights.end());

    int bw = n-1;
    int fw = 0;
    int result = 0;
    while (bw >= fw) {
        int fit = weights[bw--];
        if (fit + weights[fw] <= x)
            fw++;
        result ++;
    }
    cout << result << endl;
    return 0;
}