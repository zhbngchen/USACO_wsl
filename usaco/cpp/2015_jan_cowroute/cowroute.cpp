#include <fstream>
#include <vector>
#include <climits>

using namespace std;

#define MaxID 1000


struct Route
{
    long long cost;
    int hops;
    Route(long long c, int h): cost(c), hops(h) {}
    Route(const Route& r): cost(r.cost), hops(r.hops) {}
};

struct RouteWithId
{
    Route route;
    int id;
    RouteWithId(const Route &r, int i): route(r), id(i) {}
};

bool lessCost(const Route & r1, const Route & r2)
{
    return r1.cost < r2.cost;
}

int main()
{
    ifstream fin("cowroute.in");
    int A, B, N;
    fin >> A >> B >> N;

    vector<vector<RouteWithId>> routes(MaxID + 1);
    for (int i = 0; i < N; i++)
    {
        int cost, count;
        fin >> cost >> count;
        vector<int> ids(count);
        for (int j = 0; j < count; j++)
        {
            fin >> ids[j];
        }

        for (int j = 1; j < count; j++)
        {
            for (int k = 0; k < j; k++)
            {
                routes[ids[k]].push_back(RouteWithId(Route(cost, j - k), ids[j]));
            }
        }
    }

    vector<bool> visited(MaxID + 1);
    vector<Route> algoResults(MaxID + 1, Route(LLONG_MAX, INT_MAX));
    algoResults[A].cost = 0;
    algoResults[A].hops = 0;
    bool done = false;
    
    while (true)
    {
        done = true;
        int leastCostId = -1;
        for (int i = 1; i <= MaxID; i++)
        {
            if (visited[i])
                continue;
            else if (leastCostId == -1 || algoResults[i].cost < algoResults[leastCostId].cost)
            {
                leastCostId = i;
                if (algoResults[leastCostId].cost != LLONG_MAX)
                {
                    done = false;
                }
            }
        }
        if (done)
            break;

        visited[leastCostId] = true;
        for (auto r: routes[leastCostId])
        {
            if (algoResults[r.id].cost > (algoResults[leastCostId].cost + r.route.cost))
            {
                algoResults[r.id].cost = algoResults[leastCostId].cost + r.route.cost;
                algoResults[r.id].hops = algoResults[leastCostId].hops + r.route.hops;
            }
            else if (algoResults[r.id].cost == (algoResults[leastCostId].cost + r.route.cost))
            {
                if (algoResults[r.id].hops > algoResults[leastCostId].hops + r.route.hops)
                {
                    algoResults[r.id].hops = algoResults[leastCostId].hops + r.route.hops;
                }
            }
        }
    }

    ofstream fout("cowroute.out");
    if (algoResults[B].cost == LLONG_MAX)
    {
        fout << "-1 -1" << endl;
    }
    else
    {
        fout << algoResults[B].cost << " " << algoResults[B].hops << endl;
    }

    return 0;
}