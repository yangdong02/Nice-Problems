/*
Link: http://codeforces.com/contest/1067/problem/B
Solution 1: (As shown in the code) From root to leaves
  Find the diameter of the tree, then check its midpoint whether or not 
  it can become the center.
Solution 2: From leaves to root
  Find all vertices with degree 1 and delete them all, and update degree
  for each new veretice with degree, check if we have already deleted not less then 
  3 verticies. If initial graph was k-multihedgehog, after deleting vertices 
  with degree 1 it would became k−1-multihedgehog. Solve it recursively
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 200200;
int n, k;
int head[maxn], nxt[maxn], ecnt = 0, deg[maxn];
int fath[maxn];
struct edge {
    int from, to;
    edge(int f = 0, int t = 0) : from(f), to(t) { }
} e[maxn];
inline void addedge(int x, int y) {
    e[++ecnt] = edge(x, y);
    nxt[ecnt] = head[x];
    head[x] = ecnt;
}
int mxdep = 1, u = 1;
int u1, u2, p1, p2, twoRoots = false;
void dfs1(int v, int dep, int fa) {
    fath[v] = fa;
    if(dep > mxdep) mxdep = dep, u = v;
    for(int i = head[v]; i ; i = nxt[i])
        if(e[i].to != fa) dfs1(e[i].to, dep + 1, v);
}
inline void getRoot() {
    dfs1(1, 1, -1);
    mxdep = 1, u1 = u;
    dfs1(u1, 1, -1);
    u2 = u;
    int len = mxdep - 1, hf = len >> 1;
    p1 = u2;
    if(len & 1) twoRoots = true;
    else twoRoots = false;
    rep(i, hf) p1 = fath[p1];
    p2 = fath[p1];
    if(len - hf != k) {printf("No\n"); exit(0);}
}
bool dfs2(int v, int fa, int dep) {
    if(deg[v] == 0) return dep == k + 1;
    if(deg[v] < 3) return false;
    for(int i = head[v]; i; i = nxt[i]) if(e[i].to != fa) {
        deg[e[i].to]--;
        if(!dfs2(e[i].to, v, dep + 1)) return false;
    }
    return true;
}
inline bool judge(int v) {
    return dfs2(v, -1, 1);
}
int main(){
    scanf("%d%d", &n, &k);
    rep(i, n - 1) {
        int x, y; scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
        deg[x]++, deg[y]++;
    }
    getRoot();
    if(judge(p1) || (twoRoots && judge(p2)))
        puts("Yes");
    else puts("No");
    return 0;
}
