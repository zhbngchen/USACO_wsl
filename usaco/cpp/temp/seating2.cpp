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
 
//#ifdef __LOCAL
    ifstream fin("seating.in");
    ofstream fout("seating.out");
    #define cin fin
    #define cout fout
//#endif

struct Node 
{
    int mg; // max gap
    int fg; // first(left) gap
    int lg; // last(right) gap

    void assignAll(int v) {
        mg = v;
        fg = v;
        lg = v;
    }

    Node(int v) {
        assignAll(v);
    }
};

#define A_EMPTY 1
#define A_FILL 2

int N, M;
int NN;
vector<Node> segT;
vi lazyT; // 0: not lazy; 1: Empty; 2: filled

void pushDown(int node, int s, int e) {
    if (lazyT[node]) { // the lazy node record update operation for all eles this node controls
        segT[node].assignAll((lazyT[node] == A_FILL ? 0 : e - s + 1)); 
        // make direct children lazy (push down lazy)
        if (s != e) {
            lazyT[node * 2] = lazyT[node];
            lazyT[node * 2 + 1] = lazyT[node];
        }
        lazyT[node] = 0;
    }    
}

void update(int node, int s, int e, int a, int b, int action) {
    pushDown(node, s, e);
    if (s > b || e < a || e >= segT.size())
        return;
    if (s >= a && e <= b) {
        lazyT[node] = action;
    }
    else {
        int mid = (s+e)/2;
        int childSize = mid - s + 1;
        update(2*node, s, mid, a, b, action);
        update(2*node+1, mid+1, e, a, b, action);
        pushDown(2*node, s, mid);
        pushDown(2*node+1, mid+1, e);
        segT[node].fg = segT[2*node].fg;
        if (childSize == segT[2 * node].fg)
            segT[node].fg += segT[2 * node + 1].fg;

        segT[node].lg = segT[2*node+1].lg;
        if (childSize == segT[2 * node + 1].lg)
            segT[node].lg += segT[2 * node].lg;
        segT[node].mg = max(max(segT[2*node].mg, segT[2*node+1].mg), segT[2*node].lg + segT[2*node+1].fg);
        segT[node].mg = max(segT[node].lg, segT[node].mg);
    }
}

void construct(int N) { // initialize segT & lazy T
    NN = 1 << (int)ceil(log2(N));
    segT.resize(2*NN, Node(0));
    lazyT.resize(2*NN);
    update(1, 0, NN - 1, 0, NN-1, A_FILL);
    update(1, 0, NN - 1, 0, N-1, A_EMPTY);
}

// Returns:
//  -1: Cannot be seated
//  0 - (n-1): beginning seated index
int query(int node, int s, int e, int size) {
    pushDown(node, s, e);
    if (segT[node].fg >= size)
        return s;
    if (segT[node].mg >= size) {
        int mid = (s+e)/2;
        int lc = query(2*node, s, mid, size);
        if (lc != -1)
            return lc;
        pushDown(2 * node + 1, mid +1, e);
        if (segT[2*node].lg + segT[2*node+1].fg >= size)
            return mid - segT[2*node].lg + 1;
        return query(2*node + 1, mid+1, e, size);
    }
    //if (segT[node].lg >= size) 
    //    return e - segT[node].lg + 1;
    return -1;
}


int main() {
    // read input
    cin >> N >> M;

    // construct segment tree
    construct(N);   

    // process each event (A/L)
    char et; // event type
    int size; // arriving size
    int a, b;
    int ret = 0;
    FOR(i, 0, M) {
        cin >> et;
        if (et == 'A') { // arrive
            cin >> size;
            int pos = query(1, 0, NN - 1, size);
            if (pos == -1) {
                ret++;
            }
            else {
                update(1, 0, NN - 1, pos, pos + size - 1, A_FILL);
            }
        }
        else { // leaving
            cin >> a >> b;
            --a; --b;
            update(1, 0, NN - 1, a, b, A_EMPTY);
        }
    }

    // write output
    cout << ret << endl;

    return 0;
}

