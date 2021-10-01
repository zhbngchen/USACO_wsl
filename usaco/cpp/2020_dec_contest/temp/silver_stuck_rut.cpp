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

vi inputCordXDirE;
vi inputCordXDirN;
vi inputCordYDirN;
vi inputCordYDirE;

vpii endCords;

Graph stopRelations;
vb stopped;

bool checkXBlocked(int startX, int destX, int y, int* stoppedBy) {
    FOR(i, 0, N) {
        if (startX <= inputCords[i].first && destX == inputCords[i].first && 
            y >= inputCords[i].second && y < endCords[i].second) {
            *stoppedBy = i;
            return true;
        }
    }
    return false;
}

bool checkYBlocked(int startY, int x, int destY, int* stoppedBy) {
    FOR(i, 0, N) {
        if (startY <= inputCords[i].second && destY == inputCords[i].second && 
            x >= inputCords[i].first && x < endCords[i].first) {
            *stoppedBy = i;
            return true;
        }
    }

    return false;
}

int main() {
    cin >> N;
    stopped.resize(N);
    FOR(i, 0, N) {
        char c;
        cin >> c;
        inputDirs.push_back(c);
        int x, y;
        cin >> x >> y;
        inputCords.push_back(make_pair(x, y));
        endCords.push_back(make_pair(x, y));
        if (c == 'N') {
            inputCordXDirN.push_back(x);
            inputCordYDirN.push_back(y);
        }
        else {
            inputCordXDirE.push_back(x);
            inputCordYDirE.push_back(y);
        }  
    }
    sort(inputCordXDirN.begin(), inputCordXDirN.end());
    sort(inputCordYDirN.begin(), inputCordYDirN.end());
    sort(inputCordXDirE.begin(), inputCordXDirE.end());
    sort(inputCordYDirE.begin(), inputCordYDirE.end());

    set<int> steps;
    vi::iterator saved_it = inputCordXDirN.begin();
    FOR(i, 0, inputCordXDirE.size())
    {
        auto it = upper_bound(saved_it, inputCordXDirN.end(), inputCordXDirE[i]);
        saved_it = it;
        while (it != inputCordXDirN.end())
        {
            steps.insert(*it - inputCordXDirE[i]);
            it ++;
        }
    }
    saved_it = inputCordYDirE.begin();
    FOR(i, 0, inputCordYDirN.size())
    {
        auto it = upper_bound(saved_it, inputCordYDirE.end(), inputCordYDirN[i]);
        saved_it = it;
        while (it != inputCordYDirE.end())
        {
            steps.insert(*it - inputCordYDirN[i]);
            it++;
        }
    }
    cout << "size of steps" << steps.size() << endl;

    bool done = false;
    int time = 0;
    for (auto cur : steps) {
        int step = cur - time;
        FOR(i, 0, N) {
            if (!stopped[i]) {
                if (inputDirs[i] == 'N')
                    endCords[i].second += step;
                else
                    endCords[i].first += step;
            }
        }
        FOR(i, 0, N) {
            if (!stopped[i])
            {
                int stoppedBy = -1;
                if (inputDirs[i] == 'N')
                {
                    if (checkYBlocked(inputCords[i].second, endCords[i].first, endCords[i].second, &stoppedBy)) {
                        stopped[i] = true;
                        stopRelations[stoppedBy].push_back(i);
                    }
                }
                else
                { // "E"
                    if (checkXBlocked(inputCords[i].first, endCords[i].first, endCords[i].second, &stoppedBy)) {
                        stopped[i] = true;
                        stopRelations[stoppedBy].push_back(i);
                    }
                }
            }
        }
        time = cur;
    }
    
    // For each stopRelations, find counts
    vi results(N);
    for (auto it = stopRelations.begin(); it != stopRelations.end(); it ++) {
        queue<int> q;
        for (auto s: it->second)
            q.push(s);
        while (!q.empty()) {
            int f = q.front();
            q.pop();
            results[it->first] += 1;
            for (auto s2: stopRelations[f])
                q.push(s2);
        }
    }
    // output
    FOR(i, 0, N)
        cout << results[i] << endl;

    return 0;
}