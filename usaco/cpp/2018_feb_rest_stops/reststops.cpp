#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
struct Grass
{
    int loc;
    int tastiness;
};
struct Less_than_key
{
    bool operator() (const Grass & struct1, const Grass& struct2)
    {
        return (struct1.tastiness < struct2.tastiness);
    }
};

int L, N, Rf, Rb;
vector<Grass> vg;

int main()
{
    ifstream fin("reststops.in");
    fin >> L >> N >> Rf >> Rb;
    vg.resize(N);
    for (int i = 0; i < N; i++)
    {
        fin >> vg[i].loc >> vg[i].tastiness;
    }
    sort(vg.begin(), vg.end(), Less_than_key());

    int lastLocation = 0;
    long long result = 0;
    long long rDiff = Rf - Rb;
    for (auto it = vg.crbegin(); it != vg.crend(); it++)
    {
        if (it->loc <= lastLocation)
        {
            continue;
        }
        result += (it->loc - lastLocation) * rDiff * it->tastiness;
        lastLocation = it->loc;
    }

    ofstream fout("reststops.out");
    fout << result << endl;
    return 0;
}