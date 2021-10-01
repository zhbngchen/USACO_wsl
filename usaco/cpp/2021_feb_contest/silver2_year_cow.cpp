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
    int N, K;
    string s;
    stringstream ss;
    cin >> s;
    ss << hex << s;
    ss >> N;
    cin >> K;

    vi years(N);
    FOR(i, 0, N) {
        cin >> years[i];
    }

    sort(years.begin(), years.end());

    vpii diffs(years.size()-1);
    FOR(i, 0, years.size()-1) {
        diffs[i].first = years[i+1] - years[i];
        diffs[i].second = i;
    }
    sort(diffs.begin(), diffs.end());

    vi bigGapsIndexes(K-2);
    int start = diffs.size() - 1;
    FOR(i, 0, K-2) {
        bigGapsIndexes[i] = diffs[start - i].second;
    }
    sort(bigGapsIndexes.begin(), bigGapsIndexes.end());

    int result = 0;
    int begin=0, end=0;
    FOR(i, 0, bigGapsIndexes.size()) {
        end = years[bigGapsIndexes[i]];
        begin = 0;
        if (i == 0) {
            begin = years[0];
        }
        else
            begin = years[bigGapsIndexes[i-1]+1];
        result += ((end+11)/12 - begin/12)*12;
    }
    begin = years[bigGapsIndexes[bigGapsIndexes.size() - 1]+1];
    end = years[years.size()-1];
    result += ((end+11)/12 - begin/12)*12;

    cout << result << endl;

    return 0;
}