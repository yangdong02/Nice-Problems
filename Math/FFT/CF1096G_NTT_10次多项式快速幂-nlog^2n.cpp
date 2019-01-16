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
          n / 2次幂，然后IDFT即可。。O(nlogn) 763 ms
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
int n, kk, l, lim, limI, r[NTT_MAXN], a[NTT_MAXN], b[NTT_MAXN], c[NTT_MAXN];

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

void ntt_pmul(int* A, int degA, int* B, int degB) {
    l = 0, lim = 1;
    while(lim <= degA + degB) lim <<= 1, l++;
    limI = inv(lim);
    for(int i = 0; i < lim; ++i) {
        r[i] = (r[i>>1] >> 1) | ((i&1) << (l-1));
    }
    ntt(A, 1);
    ntt(B, 1);
    for(int i = 0; i < lim; ++i) A[i] = muln(A[i], B[i]), B[i] = 0;
    ntt(A, -1);
}

int da, db, dc;

int main() {
    scanf("%d%d", &n, &kk); n >>= 1;
    rep(i, kk) {
        int x; scanf("%d", &x);
        b[x]++;
    }
    for(db = 9; db >= 0; --db)
        if(b[db]) break;
    for(int i = 0; i <= db; ++i) c[i] = b[i];
    a[0] = 1;
    dc = db, da = 0;
    while(n) {
        if(n & 1) {
            ntt_pmul(a, da, c, db);
            da += db;
            for(int i = 0; i <= db; ++i) c[i] = b[i];
            dc = db;
        }
        n >>= 1;
        ntt_pmul(b, db, c, db);
        db += db;
        for(int i = 0; i <= db; ++i) c[i] = b[i];
        dc = db;
    }
    
    int ans = 0;
    for(int i = 0; i <= da; ++i)
        ans = mo(ans + muln(a[i], a[i]));
    printf("%d\n", ans);
    return 0;
}
