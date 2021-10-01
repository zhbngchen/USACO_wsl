#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define pb push_back
#define pi pair<int, int>
#define f first
#define mp make_pair
#define s second

#ifdef __LOCAL
    ifstream fin("in");
    ofstream fout("out");
    #define cin fin
    #define cout fout
#endif

ll dp[100001][101];
const ll MOD = (10e8)+7;
int main() {
		int n, m;
		cin >> n >> m;
		int arr[n];
		for (int i = 0; i < n; i++) {
				cin >> arr[i];
		}
		if(arr[0] == 0) {
				fill(dp[0], dp[0]+101, 1);
		} else{
				dp[0][arr[0]] = 1;
		}
		for (int i = 1; i < n; i++) {
				if(arr[i] == 0) {
						for (int j = 1; j <= m; j++) {
								dp[i][j] += dp[i-1][j];
								if(j - 1 > 0) dp[i][j] += dp[i-1][j-1];
								if(j + 1 <= m) dp[i][j] += dp[i-1][j+1];
								dp[i][j] %= MOD;
						}
				} else {
						dp[i][arr[i]] += dp[i-1][arr[i]];
						if(arr[i] - 1 > 0) dp[i][arr[i]] += dp[i-1][arr[i]-1];
						if(arr[i] + 1 <= m) dp[i][arr[i]] += dp[i-1][arr[i]+1];
						dp[i][arr[i]] %= MOD;
                        cout << dp[i] << endl;
                        cout << arr[i] << endl;
                        cout << dp[i][arr[i]] << endl;
				}
                if (i > 50000)
                    cout << "test" << endl;
		}
		ll ans = 0;
		for (int i = 1; i <= m; i++) {
				ans += dp[n-1][i];
				ans %= MOD;
		}
		cout << ans;
}