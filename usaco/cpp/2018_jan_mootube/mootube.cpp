#include <fstream>
#include <queue>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

int n, Q;

#define N 5000

struct Edge 
{
    int v;
    long long w;
    Edge(int x, long long y) : v(x), w(y) {}
};

int main()
{
    ifstream fin("mootube.in");
    fin >> n >> Q;

    vector<vector<Edge>> ve(n+1);
    
    for (int i = 0; i < n - 1; i++)
    {
        int p, q;
        long long r;
        fin >> p >> q >> r;
        ve[p].push_back(Edge(q, r));
        ve[q].push_back(Edge(p, r));
    }

    ofstream fout("mootube.out");
    for (int i = 1; i <= Q; i++)
    {
        long long k;
        int v;
        fin >> k >> v;

        vector<bool> visited(N+1);
        
        queue<int> qi;
        qi.push(v);
        visited[v] = true;
        int count = 0;
        while (!qi.empty())
        {
            int cur = qi.front();
            qi.pop();
            for (Edge e : ve[cur])
            {
                if (e.w >= k && !visited[e.v])
                {
                    qi.push(e.v);
                    count++;
                    visited[e.v] = true;
                }
            }
        }
        fout << count << endl;
    }
    return 0;
}