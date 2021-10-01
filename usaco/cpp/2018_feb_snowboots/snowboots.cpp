#include <bits/stdc++.h>
//#include <fstream>
//#include <iostream>
//#include <vector>

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

const int MAX_TILES = 250;
const int MAX_BOOTS = 250;
int N, B;
vi tileDepth(MAX_TILES);
vi bootDepth(MAX_BOOTS);
vi bootSteps(MAX_BOOTS);
vb tileStepable(MAX_TILES);

int main()
{
    ifstream fin("snowboots.in");
    
    fin >> N >> B;
    
    for (int i = 0; i < N; i++)
    {
        fin >> tileDepth[i];
    }
    for (int i = 0; i < B; i++)
    {
        fin >> bootDepth[i] >> bootSteps[i];
    }

    tileStepable[0] = true;

    for (int i = 0; i < B; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ( tileStepable[j])
            {
                for (int k = 1; k <= bootSteps[i]; k++)
                {
                    if (!tileStepable[j+k] && bootDepth[i] >= tileDepth[j+k])
                    {
                        if (j+k == N-1)
                        {
                            ofstream fout("snowboots.out");
                            fout << i << endl;
                            return 0;
                        }
                        tileStepable[j+k] = true;
                        break;
                    }
                }
            }
        }
    }
    cout << "Error, should not be here" << endl;
    return 1;
}