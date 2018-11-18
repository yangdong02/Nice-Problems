/*
Link: https://codeforces.com/contest/1077/problem/F2
Source: Codeforces Round #521 (Div. 3)
Solution:
  State:
    Let dp[i,j] be the maximum total beauty of pictures if Vova
    is at the i-th picture now, the number of remaining reposts 
    is j and Vova reposted the i-th picture
  Initial Value: dp[0, x] = 0. For all the others dp[i, j] = -1
  Transition:
     For p in [i−k;i−1]  dp[i,j] = max(dp[i,j], dp[p,j+1]+a[i])
  Optimization: Monotone queue O(nx) or segment tree O(nxlogk)
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define int long long
using namespace std;
typedef long long ll;
const int maxn = 5020;
ll dp[maxn][maxn];
int n, k, x, a[maxn];

struct monoqueue_mx {
    deque<ll> a;
    ll front, rear;
    monoqueue_mx() { front = 1, rear = 0; }
    inline bool empty() { return a.empty(); }
    inline ll Max() { return empty() ? -1 : a.front(); }
    inline ll Back() { return a.back(); }
    inline void Del(int _x) { if(a.front() == _x) a.pop_front(); }
    inline void Ins(int _x) {
        while(!empty() && Back() < _x) a.pop_back();
        a.push_back(_x);
    }
} q[maxn];

signed main() {
    scanf("%lld%lld%lld", &n, &k, &x);
    rep(i, n) scanf("%lld", &a[i]);
    memset(dp, -1, sizeof dp);
    dp[0][x] = 0, q[x].Ins(0);
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= x; ++j) {
            int mx = q[j+1].Max();
            if(i >= k) q[j].Del(dp[i-k][j]);
            if(mx != -1) {
                dp[i][j] = mx + a[i];
                q[j].Ins(dp[i][j]);
                printf("dp[%lld][%lld] = %lld\n", i, j, dp[i][j]);
            }
        }
    }
    ll ans = -1;
    for(int i = n - k + 1; i <= n; ++i) {
        if(dp[i][0] >= 0)
            ans = max(ans, dp[i][0]);
    }
    if(ans < 0) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
