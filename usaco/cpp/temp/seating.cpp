/*
PROG: shopping
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
typedef map<int, int> mii;
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a))

struct Node {
    int firstGap;
    int maxGap;
    int lastGap;
};

void updateFromChildren(vector<Node>& segTree, int index) {
    int child1 = index*2;
    int child2 = index*2 + 1;
    if (segTree[child1].maxGap == 0) {
        segTree[index].firstGap = 0;
        segTree[index].maxGap = segTree[child2].maxGap;
        segTree[index].lastGap = segTree[child2].lastGap;
    }
    else if (segTree[child2].maxGap == 0) {
        segTree[index].firstGap = segTree[child1].firstGap;
        segTree[index].maxGap = segTree[child1].maxGap;
        segTree[index].lastGap = 0;
    }
    else if (segTree[child1].firstGap == segTree[child1].maxGap &&
        segTree[child1].maxGap == segTree[child1].lastGap &&
        segTree[child2].firstGap == segTree[child2].maxGap &&
        segTree[child2].maxGap == segTree[child2].lastGap) {
            segTree[index].firstGap = segTree[index].maxGap = segTree[index].lastGap = segTree[child1].maxGap + segTree[child2].maxGap;
    }
    else if (segTree[child1].firstGap == segTree[child1].maxGap &&
             segTree[child1].maxGap == segTree[child1].lastGap) {
        segTree[index].firstGap = segTree[child1].firstGap + segTree[child2].firstGap;
        segTree[index].maxGap = max(segTree[index].firstGap, segTree[child2].lastGap);
        segTree[index].lastGap = segTree[child2].lastGap;
    }
    else if (segTree[child2].firstGap == segTree[child2].maxGap &&
             segTree[child2].maxGap == segTree[child2].lastGap) {
        segTree[index].firstGap = segTree[child1].firstGap;
        segTree[index].lastGap = segTree[child1].lastGap + segTree[child2].maxGap;
        segTree[index].maxGap = max(segTree[child1].maxGap, segTree[index].lastGap);
    }
    else {
        segTree[index].firstGap = segTree[child1].firstGap;
        segTree[index].lastGap  = segTree[child2].lastGap;
        segTree[index].maxGap = max(segTree[child1].lastGap + segTree[child2].firstGap, (segTree[child1].maxGap, segTree[child2].maxGap));
    }
}

void updateRangeFromChildren(vector<Node>& segTree, int start, int end) {
    while (start < end) {
        FOR(i,start,end+1)
            updateFromChildren(segTree, i);
        start /= 2;
        end /= 2;
    }
    while (true) {
        updateFromChildren(segTree, start);
        if (start == 1) break;
        start /= 2;
    }
}

int realPosition(int index, int arraySize) {
    int ret = index;
    while (index < arraySize) {
        ret = index;
        index *= 2;
    }
    return ret;
}

int firstSeating(vector<Node>& segTree, int index, int groupSize) {
    if (segTree[2*index].maxGap >= groupSize) {
        return firstSeating(segTree, 2*index, groupSize);
    }
    else if (segTree[2*index].lastGap + segTree[2*index+1].firstGap >= groupSize) {
        return realPosition(2*index+1, segTree.size()) - segTree[2*index].lastGap;
    }
    else if (segTree[2*index+1].maxGap >= groupSize) {
        return firstSeating(segTree, 2*index+1, groupSize);
    }
    return -1;
}

void clearNode(Node& node) {
    node.firstGap = 0;
    node.maxGap = 0;
    node.lastGap = 0;
}

void setNode(Node& node) {
    node.firstGap = 1;
    node.maxGap = 1;
    node.lastGap = 1;
}

int main() {
    ofstream fout("seating.out");
    ifstream fin("seating.in");

    int N, M;
    fin >> N >> M;
    int sizeOfPowerTwo = pow(2, ceil(log2(N)));
    vector<Node> segTree(2*sizeOfPowerTwo);
    FOR(i, sizeOfPowerTwo, sizeOfPowerTwo+N) {
        setNode(segTree[i]);
    }

    updateRangeFromChildren(segTree, sizeOfPowerTwo/2, sizeOfPowerTwo - 1);

    int result = 0;
    FOR(i,0,M) {
        char action;
        int p, a, b;
        fin >> action;
        if (action == 'A') {
            fin >> p;
            int start=firstSeating(segTree, 1, p);
            if (start != -1) {
                FOR(i, start, start + p) {
                    clearNode(segTree[i]);
                }
                updateRangeFromChildren(segTree, (start)/2, (start + p - 1)/2);
            }
            else
                result++;
        }
        else { // 'L'
            fin >> a >> b;
            FOR(i,sizeOfPowerTwo+a-1, sizeOfPowerTwo+b) {
                setNode(segTree[i]);
            }
            updateRangeFromChildren(segTree, (sizeOfPowerTwo + a-1)/2, (sizeOfPowerTwo + b-1)/2);
        }
    }

    fout << result << endl;
    return 0;
}