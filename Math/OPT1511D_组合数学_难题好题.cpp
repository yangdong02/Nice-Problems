/*
  Link: ( Not public, See problem statement )
  Source: OpenTrains - Petrozavodsk Winter-2018. Jagiellonian U Contest.
  Date: 2018-12-06
  Status: Accepted (+)
  Difficulty: 2500
  Tag: Math, Combinatorics
  Solution:
    这是我做过的第一道开火车题！这是一道很好的组合数学题。
    1. 题目可以转化为下面的形式：给出一个n * n的正方形点阵，
       其中左下角a * a的小直角三角形被打叉，右上角(n - a) * (n - 1)的
       小直角三角形被打叉，要求在没有被打叉的点中选取n个，使得每行每列
       都有且只有一个点被选中。例如：第二个样例n = 5, a = 2解释如下：
       ..XXX
       ...XX
       ....X
       X*...
       XX...
    2. 这个图形很不好计数，我们分开考虑。首先考虑与左下角小三角形互补的
       点组成的三角形（上图中的*处）。我们枚举在这个区域选取的点的个数l 
       (0 <= l < a)，这个区域选点方案数和斯特林数有关，但是a比较小，也
       可以直接跑一个O(a ^ 2)的dp，转移方程：
       dp[i][j] = dp[i-1][j] + dp[i-1][j-1] * (i-j+1)
       之后，问题的图形就变成了下面一种形态，右下角是一个不可选的矩形，右
       上角是不可选三角形。即对以下形态计数：
       .|XXX    ..XXX
       .|.XX    ...XX
       .|..X or ....X  (划+-|线的方格无效)
       -+---    XX...
       X|...    XX...
      (l = 1)   (l = 0) 
    3. 这个时候再用一遍容斥原理。设在右下角至少取x个点的方法数为g(x)，则答案为
       \sum_{x=0}^{n} g(x) * (-1)^x
       下面我们计算g(x)。这也要分为两部分。
       首先是左下角正方形。方案数为在a列中选x列，然后这x列中每一列取一个数保
       证不同行，一共是C(a, x) * P(a, x)，程序中用black表示。
       然后是除去左下角正方形选过的点之后的图形，实际上是正方形去掉了右上角。
       从右往左按照乘法原理计数，答案为(a-l-c)^(n-a) * factorial(a-l-c)。
       程序中用white表示。
Complexity: O(a^3 + a^2 log n)
    组成：枚举l是O(a)的，对于每一个l，计算左下角dp是O(a^2)，其余的计数容斥原理
    贡献O(a)，而容斥原理每一项都要用到快速幂的一个log，因此为O(a^3 + a^2logn)
*/


#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 1002000, maxa = 220, mod = 1000000007;

int n, a, T, dp[maxa][maxa], fac[maxn], ifac[maxn];

inline int addn(int x, int y) {
    int ret = x + y;
    while(ret >= mod) ret -= mod;
    while(ret < 0) ret += mod;
    return ret;
}
inline int muln(int x, int y) { return 1LL * x * y % mod; }
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = muln(x, x))
        if(y & 1) ret = muln(ret, x);
    return ret;
}
inline void init_fac() {
    fac[1] = ifac[1] = fac[0] = ifac[0] = 1;
    for(int i = 2; i <= 1000000; ++i) fac[i] = muln(fac[i-1], i);
    ifac[1000000] = qpow(fac[1000000], mod - 2);
    for(int i = 1000000 - 1; i > 1; --i) ifac[i] = muln(ifac[i + 1], i + 1);
}
inline int C(int from, int choose) { return muln(fac[from], muln(ifac[choose], ifac[from-choose])); }
inline int P(int from, int choose) { return muln(fac[from], ifac[from - choose]); }

int Put_LD(int l) {
    memset(dp[0], 0, sizeof dp[0]);
    dp[0][0] = 1;
    for(int i = 1; i < a; ++i) {
        dp[i][0] = dp[i-1][0];
        for(int j = 1; j <= l; ++j)
            dp[i][j] = addn(dp[i-1][j], muln(dp[i-1][j-1], i-j+1));
    }
    return dp[a-1][l];
}

inline int calc(int l, int c) {
    int black = muln( C(a - l, c), P(a - l, c) );
    int white = muln( qpow(a-l-c, n-a), fac[a-l-c] );
    return muln(black, white);
}

int main() {
    init_fac();
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &a);
        int ans = 0, p1 = 1, p2 = 0, sgn = 1;
        for(int l = 0; l < a; ++l) {
            p1 = Put_LD(l), sgn = 1, p2 = 0;
            for(int c = 0; c < a; ++c) { 
                // 这里理应是c <= a，但是等于时答案为0，可以忽略
                p2 = addn(p2, sgn * calc(l, c));
                sgn = -sgn;
            }
            ans = addn(ans, muln(p1, p2));
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
