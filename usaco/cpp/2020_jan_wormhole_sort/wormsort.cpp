#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
struct Edge {
    int v;
    int w;
    Edge(int x, int y): v(x), w(y) {}
};
vector<vector<Edge>> edges;
vector<int> loc;
vector<int> groups;

//#define N 100001
//vector<Edge> edges[N];
//int loc[N];
//int groups[N];

void dfs(int vertex, int groupId, int mid)
{
    if (groups[vertex] != 0)
    {
        return;
    }
    groups[vertex] = groupId;
    for (int i = 0; i < edges[vertex].size(); i++)
    {
        if (edges[vertex][i].w >= mid)
        {
            dfs(edges[vertex][i].v, groupId, mid);
        }
    }
}

bool verify(int mid)
{
    //fill(groups.begin(), groups.end(), 0);
    for_each(groups.begin(), groups.end(), [](int& v){ v = 0;});
    //memset(groups, 0, sizeof(groups));
    int groupId = 1;
    for (int i = 1; i <= n; i++)
    {
        if (groups[i] == 0)
        {
            dfs(i, groupId ++, mid);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (groups[i] != groups[loc[i]])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream fin("wormsort.in");
    fin >> n >> m;
    loc.resize(n+1);
    edges.resize(n+1);
    groups.resize(n+1);
    for (int i = 1; i <= n; i++)
    {
        fin >> loc[i];
    }

    int maxW = 0;
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        fin >> x >> y >> w;
        edges[x].push_back(Edge(y, w));
        edges[y].push_back(Edge(x, w));
        if (maxW < w)
        {
            maxW = w;
        }
    }

    int l = 0;
    int r = maxW;
    int result = 0;
    while (l <= r)
    {
        int mid = l + (r-l)/2;
        if (verify(mid))
        {
            l = mid + 1;
            result = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    if (result >= maxW)
    {
        result = -1;
    }
    ofstream fout("wormsort.out");
    fout << result << endl;

    return 0;
}