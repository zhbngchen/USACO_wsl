#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, C;
vector<int> arrivalTimes;

bool verify(int val)
{
    int numBus = 0;
    int countCows = 0;
    int startTime = arrivalTimes[0];
    for (int time : arrivalTimes)
    {
        if (countCows == 0) // new bus
        {
            startTime = time;
            countCows = 1;
        }
        else if ((time - startTime) > val) // time up, finish previous bus and get new bus
        {
            countCows = 1;
            numBus ++;
            startTime = time;
        }
        else
        {
            countCows ++;
        }
        if (countCows >= C) // bus full
        {
            countCows = 0;
            numBus++;
        }
        if (numBus > M) 
            return false;
    }
    if (countCows > 0) numBus ++;
    if (numBus > M)
        return false;

    return true;
}

int main()
{
    ifstream fin("convention.in");
    fin >> N >> M >> C;
    arrivalTimes.resize(N);
    for (int i = 0; i < N; i++)
        fin >> arrivalTimes[i];
    sort(arrivalTimes.begin(), arrivalTimes.end());

    int l = 1;
    int r = arrivalTimes[arrivalTimes.size() - 1] - arrivalTimes[0];
    int result = 0;
    while (l <= r)
    {
        int m = l + (r - l)/2;
        if (verify(m))
        {
            r = m - 1;
            result = m;
        }
        else
        {
            l = m + 1;
        }
    }

    ofstream fout("convention.out");
    fout << result << endl;

    return 0;
}