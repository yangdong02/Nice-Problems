/*
  Link: https://codeforces.com/contest/1096/problem/G
  Source: Educational Codeforces Round 57 (Rated for Div. 2)
  Date: 2019-01-16
  Status: Accepted
  Difficulty: 2400
  Tag: FFT, NTT, divide and conquer
  Solution:
    等价于求一个9次以内的多项式的n次方。
    Sol1: NTT+快速幂 O(nlog^2n) 4992 ms
    Sol2：利用NTT的本质。DFT之后，我们只需要把点值表示的那些点求出
          n / 2次幂，然后IDFT即可。 O(nlogn) 763 ms
*/

#include<bits/stdc++.h>

#pragma GCC optimize(3,"Ofast","inline")
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int NTT_MAXN = 4500200, MOD = 998244353;
inline int muln(int x, int y) { return 1LL * x * y % MOD; }
inline int mo(int x) { while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; }
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = muln(x, x))
        if(y & 1) ret = muln(ret, x);
    return ret;
}
inline int inv(int x) { return qpow(x, MOD - 2); }

const int G = 3, Gi = 332748118;
int n, kk, l, lim, limI, r[NTT_MAXN], a[NTT_MAXN];

void ntt(int *A, int dft) {
    for(int i = 0; i < lim; ++i)
        if(i < r[i]) swap(A[i], A[r[i]]);
    for(int mid = 1; mid < lim; mid <<= 1) {
        int wn = qpow(dft == 1 ? G : Gi, (MOD - 1) / (mid << 1));
        for(int len = mid << 1, j = 0; j < lim; j += len) {
            int w = 1;
            for(int k = 0; k < mid; ++k, w = muln(w, wn)) {
                int x = A[j + k], y = muln(w, A[j + k + mid]);
                A[j + k] = mo(x + y);
                A[j + k + mid] = mo(x - y);
            }
        }
    }
    if(dft == -1) for(int i = 0; i < lim; ++i) A[i] = muln(A[i], limI);
}

void ntt_init(int deg) {
    l = 0, lim = 1;
    while(lim <= deg) lim <<= 1, l++;
    limI = inv(lim);
    for(int i = 0; i < lim; ++i) {
        r[i] = (r[i>>1] >> 1) | ((i&1) << (l-1));
    }
}


int main() {
    scanf("%d%d", &n, &kk); n >>= 1;
    ntt_init(10 * n);
    rep(i, kk) {
        int x; scanf("%d", &x);
        a[x]++;
    }
    
    ntt(a, 1);
    for(int i = 0; i < lim; ++i) a[i] = qpow(a[i], n);
    ntt(a, -1);

    int ans = 0;
    for(int i = 0; i < 10 * n; ++i)
        ans = mo(ans + muln(a[i], a[i]));
    printf("%d\n", ans);
    return 0;
}
