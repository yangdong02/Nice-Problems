/*
Link: https://codeforces.com/contest/1076/problem/E
Source: Educational Codeforces Round 54 (Rated for Div. 2)
Solution:
  To solve this problem we can use a data structure which allows
  to add some value on segment and get a value from some point 
  (Fenwick tree, segment tree or anything you are familliar with).

  Let's run DFS from the root while maintaining current depth. When 
  entering a vertex u on depth h, let's consider all queries having vi = u
  , and for each such query add x_i on segment [h,h+d_i]. Then for current 
  vertex u the answer is the value in point h.

  When leaving vertex uu we need to rollback everything we have done: 
  for all queries having vi = u subtract x_i on segment [h,h+d_i].
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define lowbit(x) ((x) & (-(x)))

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 600300;

int n, q;
vector<int> G[maxn];
vector<pii> qs[maxn];

struct Fenwick {
    ll c[maxn];
    inline void add(int x, ll d) {
        for(; x <= n; x += lowbit(x))
            c[x] += d;
    }
    inline ll sum(int x) {
        ll ret = 0;
        for(; x; x -= lowbit(x))
            ret += c[x];
        return ret;
    }
    inline void Modify(int l, int r, ll d) {
        add(l, d);
        add(r + 1, -d);
    }
    inline ll Query(int x) {
        return sum(x);
    }
} f;

ll ans[maxn];
void dfs(int v, int fa, int dep) {
    for(auto qu : qs[v])
        f.Modify(dep, dep + qu.first, qu.second);
    ans[v] = f.Query(dep);
    for(auto u : G[v]) if(u != fa) dfs(u, v, dep + 1);
    for(auto qu : qs[v])
        f.Modify(dep, dep + qu.first, -qu.second);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    scanf("%d", &q);
    while(q--) {
        int x, d, v;
        scanf("%d%d%d", &x, &d, &v);
        qs[x].push_back({min(d, n + 10), v});
    }
    dfs(1, -1, 1);
    rep(i, n) printf("%lld%c", ans[i], " \n"[i==n]);
    return 0;
}
