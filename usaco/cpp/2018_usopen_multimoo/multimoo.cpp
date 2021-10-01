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

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a)) 

typedef map<int, vector<int>> Graph;
typedef map<pii, Graph> Graphs;

int N;
vvi inputCowIds;
vi regionIds;
vi regionCounts;

Graph cellIdGraph;

Graphs cowIdPairGraphs;

int getCellId(int row, int col) {
    return row * inputCowIds.size() + col;
}

void dfs(Graph& graph, int index, vb& visited, function<void(int)> func) {
    if (visited[index])
        return;
    visited[index] = true;
    func(index);
    for (auto neighbor : graph[index]) {
        dfs(graph, neighbor, visited, func);
    }
}

int main() {

    ifstream fin("multimoo.in");
    fin >> N;
    inputCowIds.resize(N, vector<int>(N));
    regionIds.resize(N*N, 0);
    FOR(i, 0, N)
        FOR(j, 0, N)
            fin >> inputCowIds[i][j];

    FOR(i, 0, N) {
        FOR(j, 0, N) {
            int cellId = getCellId(i, j);
            cellIdGraph[cellId];
            if (i < N - 1) {
                int rightCellId = getCellId(i+1, j);
                if (inputCowIds[i][j] == inputCowIds[i+1][j]) {
                    cellIdGraph[cellId].push_back(rightCellId);
                    cellIdGraph[rightCellId].push_back(cellId);
                }
            }
            if (j < N - 1) {
                int downCellId = getCellId(i, j+1);
                if (inputCowIds[i][j] == inputCowIds[i][j+1]) {
                    cellIdGraph[cellId].push_back(downCellId);
                    cellIdGraph[downCellId].push_back(cellId);
                }
            }
        }
    }

    int result1 = 0;
    int regionId = 0;
    vb visited(cellIdGraph.size());
    for (auto cellIdGraphVal : cellIdGraph) {
        if (!visited[cellIdGraphVal.first])
        {
            int cellId = cellIdGraphVal.first;
            regionCounts.push_back(0);
            dfs(cellIdGraph, cellId, visited, [&result1, regionId](int index) {
                regionCounts[regionId]++;
                if (result1 < regionCounts[regionId]) {
                    result1 = regionCounts[regionId];
                }
                regionIds[index] = regionId;
            });
            regionId++;
        }
    }

    FOR(i, 0, N) {
        FOR(j, 0, N) {
            int cellId = getCellId(i, j);
            if (i < N - 1 && inputCowIds[i][j] != inputCowIds[i+1][j]) {
                int minVal = min(inputCowIds[i][j], inputCowIds[i+1][j]);
                int maxVal = max(inputCowIds[i][j], inputCowIds[i+1][j]);
                Graph& graph = cowIdPairGraphs[pii(minVal, maxVal)];

                int rightCellId = getCellId(i+1, j);
                graph[regionIds[cellId]].push_back(regionIds[rightCellId]);
                graph[regionIds[rightCellId]].push_back(regionIds[cellId]);
            }
            if (j < N - 1 && inputCowIds[i][j] != inputCowIds[i][j+1]) {
                int minVal = min(inputCowIds[i][j], inputCowIds[i][j+1]);
                int maxVal = max(inputCowIds[i][j], inputCowIds[i][j+1]);
                Graph& graph = cowIdPairGraphs[pii(minVal, maxVal)];

                int downCellId = getCellId(i, j+1);
                graph[regionIds[cellId]].push_back(regionIds[downCellId]);
                graph[regionIds[downCellId]].push_back(regionIds[cellId]);
            }
        }
    }

    int result2 = 0;
    for (auto &graph : cowIdPairGraphs) {
        vb visited(regionCounts.size());
        int count = 0;
        for (auto &graphVal : graph.second) {
            if (!visited[graphVal.first]) {
                int regionId = graphVal.first;
                dfs(graph.second, regionId, visited, [&count, &result2](int index) {
                    count += regionCounts[index];
                    if (result2 < count)
                        result2 = count;
                });
            }
        }
    }

    ofstream fout("multimoo.out");
    fout << result1 << endl << result2 << endl;
    return 0;
}