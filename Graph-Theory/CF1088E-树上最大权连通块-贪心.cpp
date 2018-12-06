/*
  Link: https://codeforces.com/problemset/problem/1088/E
  Source: Codeforces Round 525 (Div 2)
  Date: 2018-12-5
  Status: Accepted (+)
  Difficulty: 1800
  Tag: Greedy, dp on tree
  Solution:
    显然如果只考虑一个联通分量的话就可以找到最大值（根据平均原理）。
    跑一遍树形dp找到最大值，之后再跑一遍相同的树形dp找方案数。方案
    数求法也很简单：如果某个子树的dp值是平均值，那么直接令答案+1，
    令dp值为0.（如果不这么做，这棵子树的联通分量会延伸到其他区域，
    而这个区域除掉这个子树剩下的区域权值必然也是最大权值，答案会变小
    1，不优秀），最后输出答案即可。
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;


const int maxn = 300300;

vector<int> G[maxn];
int a[maxn], n, cnt = 0;
ll dp1[maxn], dp2[maxn], _max = -0x3f3f3f3f3f3f3f3fLL;

void dfs1(int v, int fa) {
    dp1[v] = a[v];
    for(auto u : G[v]) {
        if(u == fa) continue;
        dfs1(u, v);
        dp1[v] += max(dp1[u], 0LL);
    }
    _max = max(_max, dp1[v]);
}

void dfs2(int v, int fa) {
    dp2[v] = a[v];
    for(auto u : G[v]) {
        if(u == fa) continue;
        dfs2(u, v);
        dp2[v] += max(dp2[u], 0LL);
    }
    if(dp2[v] == _max) {
        cnt++;
        dp2[v] = 0;
    }
}
int main() {
    scanf("%d", &n);
    rep(i, n) scanf("%d", &a[i]);
    for(int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    printf("%lld %d\n", 1LL * _max * cnt, cnt);
    return 0;
}
