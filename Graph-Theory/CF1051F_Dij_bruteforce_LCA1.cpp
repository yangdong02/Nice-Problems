// This problem requires the participant to have a comprehensive coding & debugging ability, for it requires: 
// Adjacent list, Dijkstra, Shortest path on tree (which includes LCA) and DSU
// The idea to solve the problem is quite easy, which depends on the key observation that m - n <= 20. We can get shortest path
// of the spanning tree, and use Dijkstra to bruteforce the shortest path between queried points and the points which are involved
// in the redundant edges.

// The problem took me a lot of time to debug, but at last I found my problem was just that I forgot to initialize the lg array!
// Need to be more careful next time. 

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= (n); ++i)
using namespace std;
typedef long long ll;
typedef pair<ll, int> pii;
const int maxn = 100020, maxm = 200020;
int anc[maxn][30], root, dep[maxn], lg[maxn];
ll pre[maxn], d[50][maxn];
inline void log_init(){
    for(register int i = 2; i <= maxn; ++i)
        lg[i] = lg[i-1] + ((1 << (lg[i-1] + 1)) == i);
}
namespace adj{
    int n, ecnt = 0, head[maxn], nxt[maxm];
    struct edge{
        int from, to, w;
        edge(int x = 0, int y = 0, int z = 0) : from(x), to(y), w(z) {}
    } e[maxm];
    inline void init(int sz){
        memset(head, 0, sizeof(int) * (sz + 10));
        ecnt = 0;
    }
    inline void addedge(int x, int y, int z){
        e[++ecnt] = edge(x, y, z);
        nxt[ecnt] = head[x];
        head[x] = ecnt;
    }
	inline void Dijkstra(int s, ll* dis){
		memset(dis, 0x3f, sizeof(ll) * (n + 5) );
		priority_queue< pii, vector<pii>, greater<pii> > pq; // <Distance, nodenumber>
		pq.push({0, s}), dis[s] = 0;
		while(!pq.empty()){
			auto cur = pq.top(); pq.pop();
			ll di = cur.first; int no = cur.second;
			if(dis[no] != di) continue;
			for(int i = head[no]; i; i = nxt[i]){
				if(dis[no] + e[i].w < dis[e[i].to]){
					dis[e[i].to] = dis[no] + e[i].w;
					pq.push({dis[e[i].to], e[i].to});
				}
			}
		}
	}
}
namespace lca{
    using namespace adj;
    int LOG;
    void dfs(int v, int fa, int depth, ll pr){
        anc[v][0] = fa, dep[v] = depth, pre[v] = pr;
        for(int i = 1; i <= LOG; ++i)
            anc[v][i] = anc[ anc[v][i-1] ][i-1];
        for(int i = head[v]; i ; i = nxt[i])
            if(e[i].to != fa) dfs(e[i].to, v, depth + 1, pr + e[i].w);
    }
    inline void init(int root){
        LOG = lg[n] + 1;
        dfs(root, root, 1, 0);
    }
    inline int LCA(int x, int y){
        if(dep[x] > dep[y]) swap(x, y);
        while(dep[y] > dep[x]) y = anc[y][ lg[dep[y] - dep[x]] ];
        if(x == y) return x;
        for(int i = lg[ dep[x] ]; i >= 0; --i)
            if(anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
        return anc[x][0];
    }
}
namespace dsu{
	int fa[maxn];
	inline void init() 	{for(register int i = 1; i <= adj::n; ++i) fa[i] = i;}
	inline int find(int x) 	{ return fa[x] == x ? x : fa[x] = find(fa[x]); }
	inline void merge(int x, int y) {x = find(x), y = find(y); if(x != y) fa[x] = y;}
	inline bool in(int x, int y) {return find(x) == find(y);}
}
int q, ed, rcnt = 0, from[44], to[44], we[44], dijcnt = 0;
int main(){
	scanf("%d%d", &adj::n, &ed);
	log_init();
	dsu::init();
	for(int i = 1; i <= ed; ++i){
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		if(dsu::in(x, y)) from[++rcnt] = x, to[rcnt] = y, we[rcnt] = w;
		else dsu::merge(x, y), adj::addedge(x, y, w), adj::addedge(y, x, w);
	}
	lca::init(1);
	rep(i, rcnt) adj::addedge(from[i], to[i], we[i]);
	rep(i, rcnt) adj::addedge(to[i], from[i], we[i]);

	rep(i, rcnt) adj::Dijkstra(from[i], d[++dijcnt]);
	rep(i, rcnt) adj::Dijkstra(to[i], d[++dijcnt]);
	scanf("%d", &q);
	while(q--){
		int x, y; ll ans;
		scanf("%d%d", &x, &y);
		ans = pre[x] + pre[y] - 2 * pre[lca::LCA(x, y)];
		for(int i = 1; i <= dijcnt; ++i)
			ans = min(ans, d[i][x] + d[i][y]);
		printf("%lld\n", ans);
	}
}
