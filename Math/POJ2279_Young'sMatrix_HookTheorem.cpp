/*
Math Approach
Problem Link: https://cn.vjudge.net/problem/POJ-2279
Blog Link: https://blog.csdn.net/ACdreamers/article/details/14549077
ans = N! / PI(down + right + 1)
Note: 
1. the Blocks must lie in this way: 
...
..
.
2. There is also a DP approach, but the memory limit is too tight
*/

#include<cstdio>
#include<cstring>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
bool vis[33][33];
int n, a[33], cnt[33];
const int divi[] = {0, 1, 2, 3, 2, 5, 2, 7, 2, 3, 2, 11, 2, 13, 2, 3, 2, 17, 2, 19, 2, 3, 2, 23, 2, 5, 2, 3, 2, 29, 2, 31, 2, 3}; 
inline void mul(int x, int tim) {
    while(x != 1) cnt[divi[x]] += tim, x /= divi[x];
}

int main(){
    while(~scanf("%d", &n) && n) {
        memset(vis, 0, sizeof vis);
        memset(cnt, 0, sizeof cnt);
        int tot = 0;
        rep(i, n) {
            scanf("%d", &a[i]);
            rep(j, a[i]) vis[i][j] = true;
            tot += a[i];
        }
        rep(i, tot) mul(i, 1);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= a[i]; ++j) {
                int k, dn, rh = a[i] - j;
                for(k = i + 1; k <= n; ++k)
                    if(!vis[k][j]) break;
                dn = k - i - 1;
                mul(dn + rh + 1, -1);
            }
        ll ans = 1;
        for(int i = 2; i <= 30; ++i) 
            rep(j, cnt[i]) ans *= i;
        printf("%lld\n", ans);
    }
    
    return 0;
}
