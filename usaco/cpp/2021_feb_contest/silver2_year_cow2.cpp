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
    int N, K;
    string s;
    stringstream ss;
    cin >> s;
    ss << hex << s;
    ss >> N;
    cin >> K;

    vi years(N+1);
    FOR(i, 1, N+1) {
        cin >> years[i];
        years[i] = (years[i] + 11) / 12;
        years[i] *= 12;
    }

    sort(years.begin(), years.end());

    vi gaps(N);
    FOR(i, 0, N) {
        gaps[i] = years[i+1] - years[i]-12;
        if (gaps[i] == -1) gaps[i] = 0;
    }

    sort(gaps.begin(), gaps.end());

    int result = years[years.size() - 1];
    int start = years[0];
    FOR(i, 0, K-1) {
        result -= gaps[gaps.size() -1 - i];
    }

    cout << result << endl;

    return 0;
}