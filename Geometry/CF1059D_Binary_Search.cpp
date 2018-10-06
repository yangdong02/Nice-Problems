// 二分的思路很好想，但是坑点很多！！（都在pretest 4 上） 也有人三分法
// 1.半径范围异常，最大可以达到1e15，inf一定要设大一点
// 2. 卡精度， 注意o * o - (o - x) * (o - x) 一定要展开写，否则会爆long double的精度
// Source: http://codeforces.com/contest/1059/problem/D
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef long double ld;
bool posi = true, nega = true;
const int maxn = 100200;
const ld eps = 1e-7L, inf = 1e15L;
int xp[maxn], yp[maxn], n, mxx = 0;
inline bool judge(ld o) {
    ld lb = -inf, ub = inf, epp = 1e-9;
    rep(i, n) {
        ld x = xp[i], y = yp[i], delta = 2 * o * x - x * x; // 注意一定要这么写！！！
        if(delta + eps < 0) return false;
        delta = sqrtl(delta);
        lb = max(lb, y - delta);
        ub = min(ub, y + delta);
        if(lb > ub + epp) return false;
    }
    if(lb > ub + epp) return false;
    return true;
}
#define ABS(x) ( (x)>0 ? (x) : (-(x)) )
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int main(){
    scanf("%d", &n);
    rep(i, n) {
        scanf("%d%d", &yp[i], &xp[i]);
        if(xp[i] > 0) nega = false;
        if(xp[i] < 0) posi = false;
    }
    if(!nega && !posi) {puts("-1"); return 0;}
    if(nega) rep(i, n) xp[i] = -xp[i];
    ld l = 0.000L, r = inf;
    int cnt = 600;
    while(cnt--) {
        ld mid = (l + r) / 2.0L;
        if(judge(mid)) r = mid;
        else l = mid;
    }
    printf("%.8Lf\n", l);
    return 0;
}
