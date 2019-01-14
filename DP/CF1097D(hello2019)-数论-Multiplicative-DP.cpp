// Key observation: the dp is multiplicative
// Link: https://codeforces.com/contest/1097/problem/D
// Source: Hello 2019
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define int ll
using namespace std;
typedef long long ll;


const int MOD = 1e9 + 7;
inline int mo(int x) {
    while(x >= MOD) x -= MOD;
    while(x < 0 ) x += MOD;
    return x;
}
inline int muln(int x, int y) { return 1LL *  x * y % MOD; }
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = muln(x, x))
        if(y & 1) ret = muln(ret, x);
    return ret;
}
inline int inv(int x) { return qpow(x, MOD - 2); }

ll n;
int k, dp[10020][66], ans = 1;
void DP(int x, int p) {
    memset(dp[0], 0, sizeof dp[0]);
    dp[0][p] = 1;
    for(int i = 1; i <= k; ++i) for(int j = 0; j <= p; ++j) dp[i][j] = 0;
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j <= p; ++j) {
            int in = inv(j + 1);
            for(int s = 0; s <= j; ++s) {
                dp[i + 1][s] = mo(dp[i + 1][s] + muln(dp[i][j], in));
            }
        }
    }
    int cur = 1, res = 0;
    for(int i = 0; i <= p; ++i) {
        res = mo(res + muln(cur, dp[k][i]));
        cur = muln(cur, x);
    }
    ans = muln(ans, res);
}
signed main() {
    scanf("%lld%lld", &n, &k);
    for(ll i = 2; i * i <= n; ++i) {
        if(n % i) continue;
        ll t = 0;
        while(n % i == 0) t++, n /= i;
        DP(i, t);
    }
    if(n != 1) DP(n, 1);
    printf("%lld\n", ans);

    return 0;
}
