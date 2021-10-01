#include <iostream>
#include <fstream>

using namespace std;

long long n, k, m;

bool ok(long long x)
{
    long long g = 0;
    long long i = 0;
    while (i < k)
    {
        long long y = (n - g) / x;
        long long daysOfY;
        if (y <= m)
        {
            daysOfY = (n - g + m - 1)/m;
            if (daysOfY > (k - i))
            {
                daysOfY = k - i;
            }
            g += m * daysOfY;
            break;
        }
        else
        {
            daysOfY = (n - g - x*y) / y + 1;
            if (daysOfY > (k - i))
            {
                daysOfY = k - i;
            }
            g += y * daysOfY;
            i += daysOfY;
        }
    }
    if (g >= n)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    ifstream fin("loan.in");
    fin >> n >> k >> m;

    long long l = 1, r = n, result = 1;
    while (l <= r)
    {
        long long middle = l + (r-l)/2;
        if (ok(middle))
        {
            l = middle + 1;
            result = middle;
        }
        else
        {
            r = middle - 1;
        }
    }
    
    ofstream fout("loan.out");
    fout << result << endl;

    return 0;
}