/*
  Link: https://codeforces.com/contest/1091/problem/E
  Source: Goodbye 2018
  Solution:
    对于平凡区间[n! * k + 1, n! * (k + 1)]，总共n！个。
    对于跨越两个排列的区间，相当于求按字典序的n!个排列中相邻排列lcp之和。
    枚举lcp长度为k, 则满足条件的情况为k * (P(n, k+1) - P(n, k))
    最后不要忘记加上原本的n!.
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int mod = 998244353, maxn = 1002000;
int fac[maxn], ifac[maxn], n, ans = 0;
inline int mo(int x) {
    while(x >= mod) x -= mod;
    while(x < 0) x += mod;
    return x;
}
inline int muln(int x, int y) { return 1LL * x * y % mod; }
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = muln(x, x))
        if(y & 1) ret = muln(ret, x);
    return ret;
}
inline int inv(int x) { return qpow(x, mod - 2); }
inline void init() {
    fac[0] = ifac[0] = 1;
    for(int i = 1; i <= 1000010; ++i) {
        fac[i] = muln(fac[i-1], i);
        ifac[i] = inv(fac[i]);
    }
}
inline int P(int x, int y) { return muln(fac[x], ifac[x - y]); }

int main() {
    init();
    cin >> n;
    ans = fac[n];
    for(int i = 1; i < n; ++i)
        ans = mo(ans + muln(i, mo(P(n, i+1) - P(n,i))));
    cout << ans << '\n';
    return 0;
}
