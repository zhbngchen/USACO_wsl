#include <iostream>
#include <fstream>
#include <vector>
//#include <utility>
#include <algorithm>

using namespace std;

int n, m;
vector<pair<long long, long long>> intervals;
//    vector<int[2]> intervals;

bool verify(long long gap)
{
    int count = 0;
    long long prev = 0;
    for (int i = 0; i < intervals.size(); i++)
    {
        if (i == 0 || (intervals[i].first - prev) >= gap)
        {
            int increased = (intervals[i].second - intervals[i].first)/gap;
            prev = intervals[i].first + increased * gap;
            count += increased + 1;
        }
        else
        {
            int increased = (intervals[i].second - prev)/gap;
            prev += increased * gap;
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
    ofstream fout("socdist.out");

    fin >> n >> m;
    cout << "n=" << n << endl;
    cout << "m=" << m << endl;

    intervals.resize(m);

    for (int i = 0; i < m; i++)
    {
        fin >> intervals[i].first >> intervals[i].second;
        //cout << "intervals[" << i << "].first=" << intervals[i].first << ", intervals[" << i << "].second=" << intervals[i].second << endl;
        //fin >> intervals[i][0] >> intervals[i][1];
        //cout << "intervals[" << i << "][0]=" << intervals[i][0] << ", intervals[" << i << "][1]=" << intervals[i][1] << endl;
    }

    sort(intervals.begin(), intervals.end());

    int left = 0;
    int right = intervals[m-1].second - intervals[0].first;
    int result = left;

    while (left <= right)
    {
        int middle = left + (right - left)/2;
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

    fout << result << endl;

    return 0;
}