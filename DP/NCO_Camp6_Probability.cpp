/*
Link: https://www.nowcoder.com/acm/contest/178/B
Solution 1: 
  pro1[color][per][cnt] denotes prob of color exists cnt times in [1, per]
  pro2[color][per][cnt] denotes prob of color exists cnt times in [per, n]
  Transition is shown in the code

Solution 2:
注意到我们不仅支持向集合中加入一个人后O(n)维护dp数组，还支持删除一个人后O(n)维护dp数组。
也就是说，给定 dp' 和 p ，可以推回 dp0 。(注意p=1的情况需要特判)
所以先 O(n^2) 求出全集的 dp 数组，然后对每个 x ，O(n) 求出不含 x 的 dp 数组即可。
时间复杂度 O(n^2)，期望得分100。
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
 
const int maxn = 2020, mod = 998244353;
inline int sub(int x, int y) { return x - y + ((x - y < 0) ? mod : 0);}
inline int add(int x, int y) { return x + y - ((x + y >= mod) ? mod : 0);}
inline int mul(int x, int y) { return 1LL * x * y % mod;}
 
int w[6][6], p[maxn][6], n, ans[maxn], v[6];
int a, b, c, d, opt, pro1[5][maxn][maxn], pro2[5][maxn][maxn];
int pre_lh[5][maxn][maxn], pre_rh[5][maxn][maxn];
inline void precalc() {
    for(int co = 1; co <= 4; ++co) {
        auto ar = pro1[co], ag = pro2[co];
        ar[0][0] = 1, ag[n + 1][0] = 1;
        ar[1][0] = sub(1, p[1][co]), ar[1][1] = p[1][co];
        for(int per = 2; per <= n; ++per) {
            ar[per][0] = mul(ar[per - 1][0], sub(1, p[per][co]));
            for(int cnt = 1; cnt <= per; ++cnt) {
                ar[per][cnt] = add( mul(ar[per - 1][cnt], sub(1, p[per][co])),
                                    mul(ar[per - 1][cnt - 1], p[per][co])       );
            }
        }
        ag[n][0] = sub(1, p[n][co]), ag[n][1] = p[n][co];
        for(int per = n - 1; per; --per) {
            ag[per][0] = mul(ag[per + 1][0], sub(1, p[per][co]));
            for(int cnt = 1; cnt <= n - per + 1; ++cnt) {
                ag[per][cnt] = add( mul(ag[per + 1][cnt], sub(1, p[per][co])),
                                    mul(ag[per + 1][cnt - 1], p[per][co]) );
            }
        }
    }
    for(int co = 1; co <= 4; ++co) {
        for(int per = 0; per <= n + 10; ++per) {
            int *l = pre_lh[co][per], *r = pre_rh[co][per];
            int *ar = pro1[co][per], *ag = pro2[co][per];
            l[0] = ar[0], r[0] = ag[0];
            for(int cnt = 1; cnt <= n + 10; ++cnt) {
                l[cnt] = add(l[cnt - 1], ar[cnt]);
                r[cnt] = add(r[cnt - 1], ag[cnt]);
            }
        }
    }
}
 
int main() {
    read(n);
    rep(i, n) {
        read(p[i][1]), read(p[i][2]);
        read(p[i][3]), read(p[i][4]);
    }
    rep(i, 4) rep(j, 4) read(w[i][j]), v[i] = add(v[i], w[i][j]);
    precalc();
    int hf = n >> 1;
    for(int mx = 1; mx <= 4; ++mx) {
        for(int per = 1; per <= n; ++per) {
            int ve = add(add(mul(p[per][1], w[mx][1]), mul(p[per][2], w[mx][2])),
                         add(mul(p[per][3], w[mx][3]), mul(p[per][4], w[mx][4]))
                     );
            for(int lh = 0; lh < per; ++lh) {
                int as;
                if(hf - lh < 0) as = 0;
                else as = pre_rh[mx][per+1][hf-lh];
                ans[per] = add(ans[per],
                  mul(ve, mul(pro1[mx][per-1][lh],
                    sub(pre_rh[mx][per+1][n-per], as))));
            }
            for(int lh = 0; lh < per; ++lh) {
                int rh = hf - lh;
                ans[per] = add(ans[per], mul(
                    mul(p[per][mx], w[mx][mx]),
                    mul(pro1[mx][per-1][lh], pro2[mx][per + 1][rh])));
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
