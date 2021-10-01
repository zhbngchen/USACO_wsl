#include <fstream>
#include <algorithm>

using namespace std;

#define N 100

bool cowsInFields[N+1][N+1];
bool rowBounds[N+1][N+1];
bool colBounds[N+1][N+1];

int groups[N+1][N+1];
int groupCounts[N*N+1];

int n, k, r;
void dfs(int i, int j, int groupId)
{
    if (groups[i][j] != 0) return;
    groups[i][j] = groupId;

    if (!rowBounds[i-1][j]) dfs(i-1, j, groupId);
    if (!rowBounds[i][j]) dfs(i+1, j, groupId);
    if (!colBounds[i][j-1]) dfs(i, j-1, groupId);
    if (!colBounds[i][j]) dfs(i, j+1, groupId);
}

int main()
{
    ifstream fin("countcross.in");

    fin >> n >> k >> r;

    for (int i = 1; i <= n; i++)
    {
        rowBounds[0][i] = true;
        rowBounds[n][i] = true;
        colBounds[i][0] = true;
        colBounds[i][n] = true;
    }

    for (int i = 0; i < r; i++)
    {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2)
        {
            colBounds[x1][min(y1, y2)] = true;
        }
        else // y1 == y2
        {
            rowBounds[min(x1, x2)][y1] = true;
        }
    }

    for (int i = 0; i < k; i++)
    {
        int x, y;
        fin >> x >> y;
        cowsInFields[x][y] = true;
    }

    int groupId = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (groups[i][j] == 0)
            {
                dfs(i, j, groupId++);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (cowsInFields[i][j] && groups[i][j] != 0)
                groupCounts[groups[i][j]] += 1;
        }
    }

    int result = 0;
    for (int i = 1; i < (groupId - 1); i++)
    {
        for (int j = i+1; j <= (groupId - 1); j++)
            result += groupCounts[i] * groupCounts[j];
    }

    ofstream fout("countcross.out");
    fout << result << endl;

    return 0;
}