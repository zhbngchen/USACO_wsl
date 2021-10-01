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

int N;
vpii inputCords;
vc inputDirs;

vi inputCordX;
vi inputCordY;

vpii endCords;
vi results;

bool checkXBlocked(int startX, int destX, int y, int* blocked) {
    FOR(i, 0, N) {
        if (startX <= inputCords[i].first && destX == inputCords[i].first && 
            y >= inputCords[i].second && y < endCords[i].second) {
            *blocked = endCords[i].first;
            return true;
        }
    }
    return false;
}

bool checkYBlocked(int startY, int x, int destY, int* blocked) {
    FOR(i, 0, N) {
        if (startY <= inputCords[i].second && destY == inputCords[i].second && 
            x >= inputCords[i].first && x < endCords[i].first) {
            *blocked = endCords[i].second;
            return true;
        }
    }

    return false;
}

int main() {
    cin >> N;
    FOR(i, 0, N) {
        char c;
        cin >> c;
        inputDirs.push_back(c);
        int x, y;
        cin >> x >> y;
        inputCords.push_back(make_pair(x, y));
        endCords.push_back(make_pair(x, y));
        inputCordX.push_back(x);
        inputCordY.push_back(y);
        results.push_back(-1);
    }
    sort(inputCordX.begin(), inputCordX.end());
    sort(inputCordY.begin(), inputCordY.end());

    set<int> steps;
    FOR(i, 0, N)
        FOR(j, i+1, N) {
            steps.insert(inputCordX[j] - inputCordX[i]);
            steps.insert(inputCordY[j] - inputCordY[i]);
        }

    int time = 0;
    for(auto cur: steps) {
        int step = cur - time;

        FOR(i, 0, N) {
            if (results[i] == -1) {
                if (inputDirs[i] == 'N')
                    endCords[i].second += step;
                else
                    endCords[i].first += step;
            }
        }
        FOR(i, 0, N) {
            if (results[i] == -1)
            {
                if (inputDirs[i] == 'N')
                {
                    int blockedY = 0;
                    if (checkYBlocked(inputCords[i].second, endCords[i].first, endCords[i].second, &blockedY))
                        results[i] = blockedY - inputCords[i].second;
                }
                else
                { // "E"
                    int blockedX = 0;
                    if (checkXBlocked(inputCords[i].first, endCords[i].first, endCords[i].second, &blockedX))
                        results[i] = blockedX - inputCords[i].first;
                }
            }
        }

        time = cur;
    }
    
    FOR(i, 0, N) {
        if (results[i] == -1)
            cout << "Infinity";
        else
            cout << results[i];

        cout << endl;
    }
    return 0;
}