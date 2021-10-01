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

int main() {
    int N,K,L;
    cin >> N >> K >> L;
    vi citations(N);
    FOR(i,0,N)
        cin >> citations[i];
    
    sort(citations.begin(), citations.end(), greater<int>());
    int availableIndex = 0;
    vi available(K, L);
    int result = 0;
    int init = -1;
    bool done = false;
    FOR(i,0,N) {
        if (citations[i] > i) {
            result = i;
            continue;
        }
        if (init == -1)
            init = i;
        int diff = i+1+(i-init) - citations[i];
        int start = availableIndex;
        bool completed = false;
        FOR(j,0,diff) {
            if (start+j < K)
                available[start+j] --;
            else
            {
                done = true;
                break;
            }
            
            if (j == diff-1) completed = true;
            if (available[start+j] == 0) {
                availableIndex ++;
                if (availableIndex == K) {
                    break;
                }
            }
        }
        if (done) break;
        if (completed)
            result = i;
    }

    cout << result+1 << endl;
    return 0;
}