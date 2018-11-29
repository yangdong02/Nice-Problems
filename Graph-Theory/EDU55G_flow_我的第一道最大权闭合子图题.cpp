/*
  Link: http://codeforces.com/contest/1082/problem/G
  Source: Educational Codeforces Round 55 (Rated for Div. 2)
  Status: Upsolved
  Tag: Graph theory -> Network flow
  Difficulty: 2400
  Solution:
    最大权闭合子图模板题。
    1. 把每条边也视为点，有点权，并向它所连的点连有向边，这时每个点都有权值。
       选定某条边之后必定选他们连向的点，这就满足闭合子图性质。那么原问题就
       变成一个求最大权闭合子图的模板（注意点权有正负，否则就平凡了）
    2. 结论：  闭合子图的最大权 = 正权值之和 - 最小割
       证明：将正权点与一源点相连，负权点与汇点相连。我们想要权值最大，自然
       初始值为正权值之和；但是这样做不一定合法，要满足合法可能会有一定代价。

       首先正权点与负权点如果连一条边，那这条边一定不能割掉，否则不满足闭合
       性质，因此这些边我们定权值为正无穷；
       
       其次我们分析代价。割掉源点与正权点的边，代表不选这个正权点，代价显然
       是点权。割掉负权点与汇点的边，代表选定这个汇点，代价显然是点权绝对值。
       由此分配边的容量。

       再往下，我们可以看到，割集与闭合子图是一一对应的，而最小割可以最小化
       代价，因此就成为了最佳方案，跑出最小割即可解决问题。
*/

#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

const int maxn = 3030, maxm = 303200;
int n, m, ss, tt;
long long tot = 0;

namespace adjlist{
    int head[maxn], nxt[maxm], ecnt = 1;
    struct Edge{
        int from, to, cap, flow;
        Edge(int a = 0, int b = 0, int c = 0, int d = 0): from(a), to(b), cap(c), flow(d){}
    } e[maxm];
    inline void addedge(int x, int y, int w){
        e[++ecnt] = Edge(x, y, w, 0);
        nxt[ecnt] = head[x];
        head[x] = ecnt;

        e[++ecnt] = Edge(y, x);
        nxt[ecnt] = head[y];
        head[y] = ecnt;
    }
    inline void init(){
        memset(head, 0, sizeof head);
        ecnt = 1;
    }
}

// Dinic template
namespace Dinic{
    using namespace adjlist;
    int n, m, s, t, d[maxn], cur[maxn];
    bool vis[maxn];
    bool BFS(){
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s), d[s] = 0, vis[s] = 1;
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(int i = head[x]; i ; i = nxt[i]){
                if(!vis[e[i].to ] && e[i].cap > e[i].flow){
                    vis[e[i].to ] = 1;
                    d[e[i].to] = d[x] + 1;
                    q.push(e[i].to );
                }
            }
        }
        return vis[t];
    }
    int DFS(int x, int a){
        if(x == t || a == 0) return a;
        ll flow = 0, f;
        for(int i = cur[x]; i ; i = nxt[i], cur[x] = i){
            if(d[x] + 1 == d[e[i].to] && (f = DFS(e[i].to, min(a, e[i].cap-e[i].flow))) > 0){
                e[i].flow += f;
                e[i ^ 1].flow -= f;
                flow += f, a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    inline ll maxflow(int so, int ta){
        s = so, t = ta;
        ll flow = 0;
        while(BFS()){
            memcpy(cur, head, sizeof cur);
            flow += DFS(s, INF);
        }
        return flow;
    }
}

using Dinic::addedge;
using Dinic::maxflow;


signed main() {
    scanf("%d%d", &n, &m);
    ss = n + m + 1, tt = n + m + 2;
    for(int i = 1; i <= n; ++i) {
        int x; scanf("%d", &x);
        addedge(i, tt, x);
    }
    for(int i = n + 1; i <= n + m; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        addedge(ss, i, w);
        addedge(i, x, INF);
        addedge(i, y, INF);
        tot += w;
    }
    printf("%lld\n", tot - maxflow(ss, tt));
}
