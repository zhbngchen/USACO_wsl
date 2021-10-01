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
typedef vector<vc> vvc;


using vsi = vector<unordered_set<int>>;
using vvb = vector<vector<bool>>;

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

#ifdef __LOCAL
    ifstream fIn("in");
    ofstream fOut("out");
    #define cin fIn
    #define cout fOut
#endif

vi citations;
int N, K, L;
bool checkFit(int m) {
    int h = m+1;
    if (m == 50138)
        cout << "test" << endl;
    if (m == 50144)
        cout << "test" << endl;
    long long shortage = h - citations[m--];
    if (shortage > K)
        return false;
    int count = 0;
    while (m >= 0 && citations[m] < h) {
        int diff = h - citations[m];
        shortage += diff;
        m--;
        count++;
    }
    if (shortage <= (long long)K * L)
        return true;
    else
        return false;
}

int main() {
    cin >> N >> K >> L;
    citations.resize(N);
    FOR(i,0,N)
        cin >> citations[i];
    
    sort(citations.begin(), citations.end(), greater<int>());

    int l = 0, r = citations.size() - 1;
    int result = 0;
    FOR(m,0,72385) {
    //while (l <= r) {
        //int m = l + (r-l)/2;
        if (checkFit(m)) {
            l = m+1;
            result = m;
        }
        else 
            r = m-1;
    }
    cout << result+1 << endl;

    return 0;
}