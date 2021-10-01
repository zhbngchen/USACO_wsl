#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
#define maxScore 10000
int main()
{
    ifstream fin("homework.in");
    int N;
    fin >> N;

    vector<int> vi(N);
    for (int i = 0; i < N; i++)
    {
        fin >> vi[i];
    }

    int total = 0;
    vector<int> results;
    int bestSum = 0;
    int bestLeftTotal = 1;
    int minimum = maxScore + 1;

    for (int i = N-1; i > 0; i--)
    {
        total += vi[i];
        if (minimum > vi[i])
        {
            minimum = vi[i];
        }
        if (i != (N - 1) && (total - minimum) * (long long)bestLeftTotal >= (long long)bestSum * (N - i - 1))
        {
            if ((total - minimum) * (long long)bestLeftTotal > (long long)bestSum * (N - i - 1))
            {
                results.clear();
            }
            results.push_back(i);
            bestSum = total - minimum;
            bestLeftTotal = N - i - 1;
        }
    }

    ofstream fout("homework.out");
    for (auto it = results.crbegin(); it != results.crend(); it++)
    {
        fout << *it << endl;
    }
    return 0;
}