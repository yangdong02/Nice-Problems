// constructive algorithm, induction, math
// First of all, if the sums have different remains toward 2, then the answer is IMPOSSIBLE
// The bruteforce approach and standard solution is shown below with different namespaces

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
#define int long long
const int maxn = 1020;
int n, x[maxn], y[maxn], odd, even;

// Bruteforce solution which is worth 300 partial score.
// Just have about 40 ones, and change them according to the parity
namespace brute{
    inline void solve() {
        int tot = 40;
        if(odd) tot--;
        printf("%d\n", tot);
        rep(i, tot) printf("%d%c", 1, i == tot ? '\n' : ' ');
        rep(i, n) {
            int rhs = x[i] > 0, uhs = y[i] > 0, lft;
            x[i] = abs(x[i]), y[i] = abs(y[i]);
            lft = (tot - x[i] - y[i]) / 2;
            rep(j, x[i]) putchar(rhs ? 'R' : 'L');
            rep(j, y[i]) putchar(uhs ? 'U' : 'D');
            rep(j, lft) printf("LR");
            putchar('\n');
        }
    }
}

// Standard solution
// We can use induction to show that if we have {1, 2^1, 2^2, 2^3, ..., 2^k} , then we can have any odd points which have
// Hamilton distance less than 2^(k+1). Thus, we can use recursion to implement this.
namespace sol{
    int a[59], k, ham;
    const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
    const char dr[] = "DULR";
    void dfs(int x, int y, int cur) {
        if(cur == 0) return;
        int chg = 1LL << (cur - 1);
        for(int dir = 0; dir < 4; ++dir) {
            int xf = x + dx[dir] * chg, yf = y + dy[dir] * chg;
            if(abs(xf) + abs(yf) < (1LL << (cur - 1)) ) {
                putchar(dr[dir]);
                dfs(xf, yf, cur - 1);
                break;
            }
        }
    }
    inline void solve() {
        rep(i, n) ham = max(ham, x[i] + y[i]) + 2;
        for(k = 0; (1LL << k) < ham; ++k) ;
        if(even) printf("%lld\n1 ", ++k + 1);
        else printf("%lld\n", ++k);
        for(int i = k; i ; --i) {
            a[i] = 1LL << (i - 1);
            printf("%lld%c", a[i], i == 1LL ? '\n' : ' ');
        }
        for(int i = 1; i <= n; ++i){
            if(even) putchar('L'), x[i]++;
            dfs(x[i], y[i], k);
            putchar('\n');
        }
    }
}
signed main(){
    scanf("%lld", &n);
    odd = even = true;
    rep(i, n) scanf("%lld%lld", &x[i], &y[i]);
    rep(i, n) {
        int sum = abs(x[i]) + abs(y[i]);
        if(sum & 1) even = false; else odd = false;
    }
    if((odd | even) == 0) {puts("-1"); return 0;}
    sol::solve();
    return 0;
}
