#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 130;
int n, a[maxn], dp[maxn][30000], mx = 0;
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n), mx = 0;
        for(int i = 1; i <= n; ++i)
            scanf("%d", &a[i]), mx = max(mx, a[i]);
        sort(a + 1, a + 1 + n);
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= mx; ++j) {
                dp[i][j] = dp[i-1][j];
                if(j >= a[i]) dp[i][j] += dp[i][j - a[i]];
                if(dp[i][j] >= 2) dp[i][j] = 2;
            }
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
            if(dp[n][a[i]] == 1) cnt++;
        printf("%d\n", cnt);
    }
}
