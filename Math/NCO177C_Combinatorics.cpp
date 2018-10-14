/* Link: https://www.nowcoder.com/acm/contest/177/C
Source: NOIP virtual contest round 5
A Nice Math Problem Combinatorics
1. Consider adding add0=s0-t0 zeros and add1=s1-t1 ones
   to make T become S
2. However, there is overcounting.
   e.g. For 000 and one 0 to add, there is only 1
   valid schedule, but it is counted 4 times.
   This is because T appears more than once in S.
   So we only count the lexicographically smallest one.
   i.e. 0 added to the end of T
3. For zeroes, we can add them in front of any 1, or at the end of the sequence
   For ones, we can add them in front of any 0, or at the end of the sequence
   We will brute force the number of 0s and 1s in the end.
   Assume there are e 0s and f 1s.
   Then, we need to distribute add0-e 0s into t1 slots
   and add1-f 1s into t0 slots. Each slot can contain any 0s or 1s
   including 0. So, this is a combinatorics problem.
   Also, pay attention to the permutation of e 0s and f 1s, which should be
   included in the answer.
4. The formula is shown in T3.png.
   add0 = s0 - t0, add1 = s1 - t1
   for e  in range(0, add0 + 1):
       for f in range(0, add1 + 1):
           ans += C(e+f, e) * C(add0-e+t1-1, t1-1) * C(add1-f+t0-1, t0-1)
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 3000, mod = 1000000007;
int s0, s1, t0, t1, add0, add1, ans, fac[maxn] = {1, 1}, ifac[maxn] = {1, 1};

inline int add(int x, int y) {return x + y - ((x + y >= mod) ? mod : 0);}
inline int mul(int x, int y) { return 1LL * x * y % mod;}
inline int mul(int x, int y, int z) { return mul(mul(x, y), z); }
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = mul(x, x)) 
        if(y & 1) ret = mul(ret, x);
    return ret;
}
inline void init_fac() {
    rep(i, 2999) fac[i] = mul(fac[i - 1], i);
    ifac[2999] = qpow(fac[2999], mod - 2);
    for(int i = 2998; i; --i)
        ifac[i] = mul(ifac[i + 1], i + 1);
}
inline int C(int x, int y) {
    if(y > x || y < 0) return 0;
    return mul(fac[x], ifac[y], ifac[x-y]);
}
int main(){
    init_fac();
    scanf("%d%d%d%d", &s0, &s1, &t0, &t1);
    if(t0 == 0 || t1 == 0) {printf("%d\n", C(s0 + s1, s1)); return 0;}
    add0 = s0 - t0, add1 = s1 - t1, ans = 0;
    for(int e = 0; e <= add0; ++e) 
        for(int f = 0; f <= add1; ++f)
            ans = add(ans, mul(C(e+f, e), C(add0-e+t1-1, t1-1), C(add1-f+t0-1, t0-1)));
    printf("%d\n", mul(ans, C(t0 + t1, t0) ) );
    return 0;
}
