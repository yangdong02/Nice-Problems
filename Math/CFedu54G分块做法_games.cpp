/*
Link: http://codeforces.com/contest/1076/problem/G
Source: Educational Codeforces Round 54 (Rated for Div. 2)
Solution 1: (FCB1234)
  In my solution I want to know for every position i — can I win if I start in this position. 
  Let's say that if I can win then this position is good.
  I say that if ai  ≡  0 mod 2 then position i is good. Why? 
  Because if there is a position j such that it is not good then I can move to it,
  otherwise I can stay in the same position and my opponent has to choose a winning position for me.

  Using this fact we can easily solve this task in O(nq) — we pick last position for which we don't know answer, 
  if it's even then it's good, otherwise it's bad and we can mark previous m positions as good.

  We can simulate this process faster if we divide out array into blocks of size  so final complexity is .
  It was possible to solve it faster in  with segment tree (it's practically the same as model solution).
*/

#include<bits/stdc++.h>
#define int long long
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }


// ====== Header ======

const int maxn = 203000, maxB = 450;
int n, m, q, a[maxn], tag[maxB], go[maxB][7][2], t;
int L[maxB], R[maxB], pos[maxn];

inline int simulate(int l, int r, int j) {
    // 以j为判断依据，从r开始检查，返回在(-inf, l)中下一个需要被检查的位置与l-1的距离
    while(l <= r) {
        if(a[r] ^ j) r -= m + 1;
        else r--;
    }
    return l - r - 1;
}

inline void Build(int b) {
    for(int i = L[b]; i <= R[b]; ++i) a[i] ^= tag[b];
    tag[b] = 0;
    for(int i = 0; i <= m; ++i) {
        go[b][i][0] = simulate(L[b], R[b] - i, 0);
        go[b][i][1] = simulate(L[b], R[b] - i, 1);
    }
}

/*
 Tag: 块是否已被修改
 go:  r = R[b] - m时前一块中最末尾需被检查的位置与R[b-1]的距离
*/

inline void Modify(int l, int r) {
    if(pos[l] == pos[r]) {
        for(int i = l; i <= r; ++i) a[i] ^= 1;
        Build(pos[l]);
        return;
    }
    for(int i = pos[l] + 1; i < pos[r]; ++i)
        tag[i] ^= 1;
    for(int i = l; i <= R[pos[l]]; ++i) a[i] ^= 1;
    for(int i = L[pos[r]]; i <= r; ++i) a[i] ^= 1;
    Build(pos[l]), Build(pos[r]);
}

inline int Query(int l, int r) {
    if(a[l] == tag[pos[l]]) return 1;

    if(pos[l] == pos[r]) {
        int p = simulate(l + 1, r, tag[pos[l]]);
        return p == 0 ? 2 : 1;
    }
    
    int p = simulate(L[pos[r]], r, tag[pos[r]]);
    int cur = pos[r] - 1;
    while(cur > pos[l]) {
        p = go[cur][p][tag[cur]];
        cur--;
    }
    p = simulate(l + 1, R[pos[l]] - p, tag[pos[l]]);
    return p == 0 ? 2 : 1;
}

signed main() {
    read(n, m, q);
    t = sqrt(n + 0.5);
    ll opt, l, r, len = n / t, d;
    rep(i, n) { read(l), a[i] = l & 1; }
    for(int i = 1; i <= t; ++i) {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
    }
    if(R[t] < n) { t++, L[t] = R[t-1] + 1, R[t] = n; }
    for(int i = 1; i <= t; ++i) {
        for(int j = L[i]; j <= R[i]; ++j) pos[j] = i;
        Build(i);
    }
    while(q--) {
        read(opt, l, r);
        if(opt == 1) { read(d); if(d & 1) Modify(l, r); }
        else printf("%lld\n", Query(l, r));
    }
    return 0;
}
