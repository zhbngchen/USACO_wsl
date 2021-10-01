#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int n, m;
vector<pair<long long, long long>> inputs;

bool verify(long long distance)
{
    int count = 0;
    long long prev = 0;

    for (int i = 0; i < m; i++)
    {
        int increased = 0;
        if (i == 0 || (inputs[i].first - prev) >= distance)
        {
            increased = (inputs[i].second - inputs[i].first)/distance;
            prev = inputs[i].first + increased * distance;
            count += increased + 1;
        }
        else
        {
            increased = (inputs[i].second - prev)/distance;
            prev += increased * distance;
            count += increased;
        }

        if (count >= n)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream fin("socdist.in");

    fin >> n >> m;

    inputs.resize(m);

    for (int i = 0; i < m; i++)
    {
        fin >> inputs[i].first >> inputs[i].second;
    }

    sort(inputs.begin(), inputs.end());

    long long left = 1, right = inputs[m-1].second - inputs[0].first;
    long long result = 0;

    while (left <= right)
    {
        long long middle = left + (right - left)/2;
        if (verify(middle))
        {
            left = middle + 1;
            result = middle;
        }
        else
        {
            right = middle - 1;
        }
    }

    ofstream fout("socdist.out");
    fout << result << endl;
}