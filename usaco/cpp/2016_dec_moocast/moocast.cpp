#include <fstream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int N;
struct PointPower {
    int x;
    int y;
    int p;
};

vector<PointPower> pp;

bool matrix[200][200];
bool groups[200];

/*void dfs(int row)
{
    groups[row] = true;

    for (int j = 0; j < N; j++)
    {
        if (j == row) continue;
        if (matrix[row][j] && !groups[j])
        {
            dfs(j);
        }
    }
}*/

int main()
{
    ifstream fin("moocast.in");
    fin >> N;

    pp.resize(N);

    for (int i = 0; i < N; i++)
    {
        fin >> pp[i].x >> pp[i].y >> pp[i].p;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                int distx = pp[i].x - pp[j].x;
                int disty = pp[i].y - pp[j].y;
                if ((distx * distx + disty * disty) <= pp[i].p * pp[i].p)
                {
                    matrix[i][j] = true;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < N; i++)
    {
        memset(groups, 0, sizeof(groups));
        //dfs(i);

        // BFS
        queue<int> qi;
        qi.push(i);
        while (!qi.empty())
        {
            int i = qi.front();
            qi.pop();
            if (groups[i]) continue;
            groups[i] = true;
            for (int j = 0; j < N; j++)
            {
                if (i != j && matrix[i][j] && !groups[j])
                {
                    qi.push(j);
                }
            }
        }

        int count = 0;
        for (int j = 0; j < N; j++)
        {
            if (groups[j]) count++;
        }
        if (count > result) result = count;
    }

    ofstream fout("moocast.out");
    fout << result << endl;

    return 0;
}