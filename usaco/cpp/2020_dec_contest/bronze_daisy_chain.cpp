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

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

int N;
vi petals;
int main() {
    cin >> N;
    petals.resize(N);
    FOR(i, 0, N) {
        cin >> petals[i];
    }

    int result = 0;
    FOR(i, 0, N) {
        
        FOR(j, 0, i+1) {
            int sum = 0;
            FOR(k, j, i+1) {
                sum += petals[k];
            }
            int count = i - j + 1;
            if ((sum % count) != 0)
                continue;
            int average = sum / count;
            FOR(k, j, i + 1)
            {
                if (average == petals[k])
                {
                    result += 1;
                    break;
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}