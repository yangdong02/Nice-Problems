#include<bits/stdc++.h>
#pragma GCC optimize("-O3", "-Ofast", "inline")
#define rep(i, n) for(register int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

inline int min(int x, int y) { return (x < y) ? x : y; }
inline int max(int x, int y) { return (x < y) ? y : x; }

const int maxn = 202000, INF = 0x3f3f3f3f;
int maxv[34][maxn * 4], minv[34][maxn * 4], n, dim, q;
int p[maxn][6];

int pos, v, ql, qr, *mx, *mn;
void change(int o, int l, int r) {
    if(l == r) { mx[o] = mn[o] = v; return; }
    int mid = (l + r) >> 1;
    if(pos <= mid) change(o << 1, l, mid);
    else change(o << 1 | 1, mid + 1, r);
    mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
    mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}
int qmax(int o, int l, int r) {
    if(ql <= l && r <= qr) return mx[o];
    int ans = -INF, mid = (l + r) >> 1;
    if(ql <= mid) ans = max(ans, qmax(o << 1, l, mid));
    if(qr > mid) ans = max(ans, qmax(o << 1 | 1, mid + 1, r));
    return ans;
}
int qmin(int o, int l, int r) {
    if(ql <= l && r <= qr) return mn[o];
    int ans = INF, mid = (l + r) >> 1;
    if(ql <= mid) ans = min(ans, qmin(o << 1, l, mid));
    if(qr > mid) ans = min(ans, qmin(o << 1 | 1, mid + 1, r));
    return ans;
}


inline void Modify(int _pos) {
    for(register int c = 0; c < (1 << dim); ++c) {
        int val = 0, d = c;
        mx = maxv[c], mn = minv[c];
        rep(i, dim) {
            if(d & 1) val += p[_pos][i];
            else val -= p[_pos][i];
            d >>= 1;
        }
        pos = _pos, v = val;
        change(1, 1, n);
    }
}

inline int Query(int l, int r) {
    int bst = -INF;
    ql = l, qr = r;
    for(register int c = 0; c < (1 << dim); ++c) {
        mx = maxv[c], mn = minv[c];
        int ax = qmax(1, 1, n);
        int in = qmin(1, 1, n);
        bst = max(bst, ax - in);
    }
    return bst;
}

int main() {
    read(n, dim);
    rep(i, n) rep(j, dim) read(p[i][j]);
    rep(i, n) Modify(i);
    read(q);
    while(q--) {
        int opt, l, r;
        read(opt, l);
        if(opt == 1) {
            rep(i, dim) read(p[l][i]);
            Modify(l);
        } else {
            read(r);
            write(Query(l, r));
            putchar('\n');
        }
    }
    
    return 0;
}
