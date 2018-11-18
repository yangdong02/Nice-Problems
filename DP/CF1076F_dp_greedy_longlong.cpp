/*
Link: http://codeforces.com/contest/1076/problem/F
Source: Educational Codeforces Round 54 (Rated for Div. 2)
Solution:
  It's easy to find the dp solution and the transition is also
  quite easy to come up with. However, bear in mind that the 
  multiplication here may OVERFLOW and we should use LONG LONG !
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define int long long
using namespace std;
typedef long long ll;

const int maxn = 300300, inf = 10000000;
int n, k, ab[maxn][2], dp[maxn][2];
signed main(){
    scanf("%lld%lld", &n, &k);
    rep(i, n) scanf("%lld", &ab[i][0]);
    rep(i, n) scanf("%lld", &ab[i][1]);
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = dp[0][1] = 0;
    for(int i = 0; i < n; ++i) {
        for(int c = 0; c <= 1; ++c) {
            int p = dp[i][c], a = ab[i+1][c], b = ab[i+1][c^1];
            int cnt = (b - 1) / k + 1;
            if(p > k) continue;
            if( !(a < cnt || a > k - p + b * k) ) 
                dp[i+1][c] = min(dp[i+1][c], max(1LL, a + p - b * k));
            if( !(a < cnt - 1 || a > b * k - p) ) {
                if(a == cnt - 1) dp[i+1][c^1] = min(dp[i+1][c^1], b-(cnt-1)*k);
                else dp[i+1][c^1] = 1;
            }
        }
    }
    if(min(dp[n][0], dp[n][1]) > inf) puts("NO");
    else puts("YES");
    return 0;
}
