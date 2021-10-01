#include <fstream>
#include <algorithm>

using namespace std;

int N, K, R;

bool cows[100][100];
bool bounds[200][100];
int groups[100][100];
int groupCounts[10001];

void dfs(int x, int y, int groupId)
{
    groups[x][y] = groupId;
    if (cows[x][y])
    {
        groupCounts[groupId] += 1;
    }

    if (x > 0 && !bounds[2 * x - 1][y] && groups[x - 1][y] == 0)
    {
        dfs(x - 1, y, groupId);
    }
    if(x < (N - 1) && !bounds[2 * x + 1][y] && groups[x + 1][y] == 0)
    {
        dfs(x + 1, y, groupId);
    }
    if (y > 0 && !bounds[2 * x][y - 1] && groups[x][y - 1] == 0)
    {
        dfs(x, y - 1, groupId);
    }
    if (y < (N - 1) && !bounds[2 * x][y] && groups[x][y + 1] == 0)
    {
        dfs(x, y + 1, groupId);
    }
}

int main()
{
    ifstream fin("countcross.in");

    fin >> N >> K >> R;

    for (int i = 0; i < R; i++)
    {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2)
        {
            bounds[2 * (x1 - 1)][min(y1, y2) - 1] = true;
        }
        else // y1 == y2
        {
            bounds[2 * min(x1, x2) - 1][y1 - 1] = true;
        }
    }

    for (int i = 0; i < K; i++)
    {
        int x, y;
        fin >> x >> y;
        cows[x - 1][y - 1] = true;
    }

    int groupId = 1;
    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < N; j ++)
        {
            if (groups[i][j] == 0)
            {
                dfs(i, j, groupId++);
            }
        }
    }
    
    int result = 0;
    for (int i = 1; i < (groupId - 1); i++)
    {
        for (int j = i+1; j < groupId; j++)
        {
            result += groupCounts[i] * groupCounts[j];
        }
    }
    
    ofstream fout("countcross.out");
    fout << result << endl;

    return 0;
}