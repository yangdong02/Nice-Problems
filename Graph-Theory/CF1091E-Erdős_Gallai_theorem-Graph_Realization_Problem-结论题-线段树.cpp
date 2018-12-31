/*
Problem Link: https://codeforces.com/contest/1091/problem/E
Source: Goodbye 2018
Theory Statement:
    请看Markdown版本的。
    Erdős–Gallai theorem
    A sequence of non-negative integers $d_{1}\geq \cdots \geq d_{n}$( $d_1\geq\cdots\geq d_n$) can be represented as the degree sequence of a finite simple graph on n vertices if and only if $d_{1}+\cdots +d_{n}$ is even and

    $$\sum _{i=1}^{k}d_{i}\leq k(k-1)+\sum _{i=k+1}^{n}\min(d_{i},k)$$

    holds for every k in $1\leq k\leq n$
Link:  https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem

Solution:
    将d降序排序之后，显然只需检查原数列，第一个数-1，前两个数-1，...这样的度数序列
    是否合法。套一下定理，可以发现每次对一个数-1只会引起定理维护的序列的区间加，检查
    是否满足定理条件只需要一个区间最大值，所以线段树搞一下就可以了。
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int BUFF_SIZE = 1 << 20;
char BUFF[BUFF_SIZE],*BB,*BE;
#define gc() (BB == BE ? (BE = (BB = BUFF) + fread(BUFF,1,BUFF_SIZE,stdin),BB == BE ? EOF : *BB++) : *BB++)

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = gc();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = gc();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = gc();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}


const int maxn = 500500;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;
int n, d[maxn];

#define ls (o << 1)
#define rs (o << 1 | 1)
ll maxv[maxn << 2], addv[maxn << 2];
inline void pushup(int o) {
    maxv[o] = max(maxv[ls], maxv[rs]);
}
inline void pushdown(int o, int l, int r) {
    if(!addv[o]) return;
    maxv[ls] += addv[o];
    maxv[rs] += addv[o];
    addv[ls] += addv[o];
    addv[rs] += addv[o];
    addv[o] = 0;
}

inline void Modify(int o, int l, int r, int ql, int qr, ll d) {
    if(ql <= l && r <= qr) {
        maxv[o] += d;
        addv[o] += d;
        return;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    if(ql <= mid) Modify(ls, l, mid, ql, qr, d);
    if(qr > mid) Modify(rs, mid + 1, r, ql, qr, d);
    pushup(o);
}
inline ll Query(int o, int l, int r, int ql, int qr) {
    if(ql <= l && r <= qr) return maxv[o];
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    ll ans = -INF;
    if(ql <= mid) ans = max(ans, Query(ls, l, mid, ql, qr));
    if(qr > mid) ans = max(ans, Query(rs, mid + 1, r, ql, qr));
    return ans;
}
inline void Build(int o, int l, int r, ll* arr) {
    addv[o] = 0;
    if(l == r) {
        maxv[o] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(ls, l, mid, arr);
    Build(rs, mid + 1, r, arr);
    pushup(o);
}

inline void Change(int p) {
    Modify(1, 1, n, p, n, -1);
    int effect = d[p]--; // k >= effect时的区间会被+1
    int rb = p - 1;
    if(effect > rb) return;
    Modify(1, 1, n, effect, rb, 1);
}

ll c[maxn], pref[maxn], tot, cnt = 0;
inline ll SumD(int l, int r) { return pref[r] - pref[l - 1]; }

int main() {
    read(n);
    rep(i, n) read(d[i]);
    sort(d + 1, d + 1 + n, greater<int>());
    rep(i, n) pref[i] = d[i] + pref[i - 1];

    tot = pref[n];
    int pos = n;
    for(int k = 1; k <= n; ++k) {
        while(d[pos] < k && pos > 0) pos--; // pos到了>=k的第一个位置
        c[k] -= 1LL * k * (k - 1);
        c[k] += pref[k];
        if(pos >= k) {
            c[k] -= SumD(pos + 1, n);
            c[k] -= 1LL * k * (pos - k);
        } else {
            c[k] -= SumD(k + 1, n);
        }
    }

    Build(1, 1, n, c);
    
    vector<int> answer;
    if(tot % 2 == 0 && Query(1, 1, n, 1, n) <= 0) 
        answer.push_back(0);
    for(int i = 1; i <= n; ++i) {
        if(d[i]) Change(i);
        else break;
        tot--, cnt++;
        if(tot & 1) continue;
        if(Query(1, 1, n, 1, n) <= 0) answer.push_back(cnt);
    }
    if(answer.size() == 0) puts("-1");
    else for(auto v : answer) printf("%d ", v);
    return 0;
}
