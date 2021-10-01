/*
PROG: nocows
LANG: C++
*/

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

int recursive(int num, int level, vvi& memo){
    if (memo[num][level])
        return memo[num][level];
    if (!level)
        return 0;
    else if (num == 1 && level >= 1)
        return 1;
    int nextNum = 1;
    int result = 0;
    while (nextNum < num) {
        result += recursive(nextNum, level - 1, memo) * recursive(num - 1 - nextNum, level - 1, memo);
        //result %= 9901;
        nextNum += 2;
    }

    memo[num][level] = result;
    return result;
}

void printArray(vvi& array) {
    for ( int x = 0; x < array.size(); x ++ ) {
        cout << "row" << x << ": ";
        for ( int y = 0; y < array[0].size(); y++ ) {
            cout << array[x][y] << " ";
        }
        cout << endl;
    }
}

int main() {
    ofstream fout ("nocows.out");
    ifstream fin ("nocows.in");
    int N, K;
    fin >> N >> K;
    vvi memo(N+1, vi(K+1));
    recursive(N, K, memo);
    if (!memo[N][K-1])
        recursive(N, K-1, memo);
    fout << (memo[N][K] +9901 - memo[N][K-1])%9901 << endl;
    printArray(memo);

    return 0;
}