#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 100000
int N;
vector<int> waitTimes;
int main()
{
    ifstream fin("lemonade.in");
    fin >> N;
    waitTimes.resize(N);
    for (int i = 0; i < N; i++)
        fin >> waitTimes[i];
    sort(waitTimes.begin(), waitTimes.end());

    int result = 0;
    for (auto it = waitTimes.crbegin(); it != waitTimes.crend(); it++)
    {
        if (*it > N)
        {
            result ++;
        }
        else if (*it < result)
        {
            break;
        }
        else
        {
            result ++;
        }
        
    }

    ofstream fout("lemonade.out");
    fout << result << endl;

    return 0;
}