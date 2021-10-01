#include "bits/stdc++.h"
#include <math.h>

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
typedef vector<bool> vb;
typedef set<int> si; 
typedef map<string, int> msi;
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

#ifdef __LOCAL
    ifstream fin("in");
    ofstream fout("out");
    #define cin fin
    #define cout fout
#endif

int recursive(const string& str1, int ind1, string& str2, int ind2, vvi& memo) {
    if (ind1 == str1.size())
        return str2.size() - ind2;
    else if (ind2 == str2.size())
        return str1.size() - ind1;
    
    if (memo[ind1][ind2] != -1)
        return memo[ind1][ind2];

    int ret = INT_MAX;
    if (str1[ind1] == str2[ind2])
        ret = recursive(str1, ind1+1, str2, ind2+1, memo);
    else {
        ret = min(ret, 1 + recursive(str1, ind1, str2, ind2 + 1, memo));     // add 1 to str1
        ret = min(ret, 1 + recursive(str1, ind1 + 1, str2, ind2, memo));     // remove 1 from str1
        ret = min(ret, 1 + recursive(str1, ind1 + 1, str2, ind2 + 1, memo)); // replace 1 in str1
    }
    memo[ind1][ind2] = ret;
    return ret;
}

int main() {
    string in1, in2;
    cin >> in1;
    cin >> in2;
    vvi memo(in1.size(), vi(in2.size(), -1));

    cout << recursive(in1, 0, in2, 0, memo);

    return 0;
}