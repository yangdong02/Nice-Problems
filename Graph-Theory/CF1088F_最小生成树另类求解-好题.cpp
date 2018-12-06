/*
  Link: https://codeforces.com/problemset/problem/1088/F
  Source: Codeforces Round 525 (Div 2)
  Date: 2018-12-5
  Status: Accepted (+)
  Difficulty: 1800
  Tag: MST, Observation, Doubling on tree
  Solution:
    有趣题。题意很显然就是求一个最小生成树，但是点数有1e5，
    任意两个节点之间都有边。这时需要一个仔细观察：原图中如果
    以最小权值的点为根，那么这棵树从任意祖先向下走到任意后代，
    点的权值必然一直增加（否则为满足条件，树要无限大）。新生
    成的树中，我们仍然以原树权值最小的点为根。对于任意节点，
    一定要选边权最小的出边，因此每条边必然向上连向祖先。更准
    确地说，连向第2^i个祖先或者根。这样只要预处理树上倍增，每
    个点都倍增一下统计最优结果就可以了。
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 500500, INF = 0x3f3f3f3f;
const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
int a[maxn], anc[maxn][21], n, root, mn = INF;
ll ans = 0;
vector<int> G[maxn];

void dfs(int v, int fa) {
    anc[v][0] = fa;
    for(int i = 1; i <= 19; ++i)
        anc[v][i] = anc[ anc[v][i-1] ][i-1];
    for(auto u : G[v]) {
        if(u == fa) continue;
        dfs(u, v);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if(a[i] < mn) mn = a[i], root = i;
    }
    for(int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(root, root);
    for(int v = 1; v <= n; ++v) {
        if(v == root) continue;
        ll res = INFL;
        for(int i = 0; i <= 19; ++i)
            res = min(res, 1LL * (i + 1) * a[ anc[v][i] ] + (ll)a[v]);
        ans += res;
    }
    printf("%lld\n", ans);
    return 0;
}
