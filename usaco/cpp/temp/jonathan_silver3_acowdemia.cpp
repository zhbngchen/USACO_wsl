
#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll; 
typedef pair<int, int> pii; 
typedef pair<ll, ll> pll; 
typedef pair<string, string> pss; 
typedef vector<int> vi; 
typedef vector<pii> vpi; 
typedef vector<vi> vvi;  
typedef vector<ll> vl; 
typedef vector<string> vs; 
typedef vector<vl> vvl;
typedef set<int> si; 
typedef map<string, int> msi;
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

#ifdef __LOCAL
    ifstream fin("in");
    ofstream fout("out");
    #define cin fin
    #define cout fout
#endif
int N, K, L;

int getMax(vl& papers){
    vector<int> added(100001);
    ll maxCN = LLONG_MIN; //Max depth
    ll total = 0; //Total amount
    ll repAdd = 0;
    FOR(i, 0, N){
        int h = i + 1;
        int diff = h - papers[i];
        if(diff > K) return i;
        else if(diff > 0) total += diff;
        repAdd += added[i]; // pick up previous saved to repAdd
        total += repAdd;

        if(total > (ll)K*L) 
            return i;

        if(papers[i] <= i) // since i will be i+1 in next loop, the index papers[i] for added[papers[i]] will not be met by following i values
            repAdd++;
        else
            added[papers[i]]++;
    }
    return N;
}


vl papers;
int main(){
    cin >> N >> K >> L;
    papers.resize(N);
    FOR(i, 0, N){
        cin >> papers[i];
    }
    sort(papers.rbegin(), papers.rend());
    cout << getMax(papers) << endl;
    
}