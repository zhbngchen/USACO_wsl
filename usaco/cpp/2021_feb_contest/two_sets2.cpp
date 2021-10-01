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

typedef vector<char> vc;
typedef vector<vc> vvc;

typedef vector<vb> vvb;

typedef vector<string> vs;
typedef vector<vs> vvs;

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
    int n;
    cin >> n;

    if ((n+1)/2%2 == 1) {
        cout << "NO" << endl;
        return 0;
    }

    vi group1, group2;
    int mid = (n+1)/2;
    int l = 1;
    int alternate = 0;
    while ((n%2 == 1 && l < mid) || (n%2 == 0 && l <= mid)) {
        int r = n + 1 - l;
        if (l + mid == r) {
            group1.push_back(l);
            group1.push_back(mid);
            group2.push_back(r);
        }
        else {
            if (alternate == 0) {
                group1.push_back(l);
                group1.push_back(r);
            }
            else {
                group2.push_back(l);
                group2.push_back(r);
            }
            alternate += 1;
            alternate %= 2;
        }
        l ++;
    }
    cout << "YES" << endl;
    cout << group1.size() << endl;
    FOR(i, 0, group1.size())
    cout << group1[i] << " ";
    cout << endl;
    cout << group2.size() << endl;
    FOR(i, 0, group2.size())
    cout << group2[i] << " ";
    cout << endl;

    return 0;
}