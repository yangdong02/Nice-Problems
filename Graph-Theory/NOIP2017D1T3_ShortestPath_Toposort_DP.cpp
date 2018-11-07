/*
Link: https://www.luogu.org/problemnew/show/P3953
Solution:
  As K <= 50 and it is a directed graph, we can consider dp.  
  use dp[vertex][left_distance_to_be_wasted] to find a O(KM) solution:
  dp[v][d] -> dp[u][d + new_wasted] Where new_wasted = d1[v]+e[i].w-d1[u]
    (d1: shortest path to vertex No.1, we can use Dijkstra)
  We should consider left_distance from 1 to K, then vertex 1 to n.
  
  The next problem is to determine the time sequence in which the dp processes
  One idea is just sort vertices by the distance to 1 , but it won't work when 0 edge exists (70 pts)
  The standard solution is to add 0 edges into a new graph. As we can see, if they become a cycle, then 
    the answer is -1, else the nearer one to vertex 1 is updated first. So we do a toposort to find if
    there is a solution and get the dp seqence.
    
  This problem needs some coding, debugging technique as the code is long. We should practice more.
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n, m, k, mod, kase = 0;
const int maxn = 400200;
int head[maxn], nxt[maxn], ecnt = 0, d1[maxn], dn[maxn];
struct edge {
    int from, to, w;
    edge(int x = 0, int y = 0, int z = 0) :
        from(x), to(y), w(z) { }
} e[maxn];
inline void addedge(int f, int t, int c) {
    e[++ecnt] = edge(f, t, c);
    nxt[ecnt] = head[f];
    head[f]   = ecnt;
}

int zdeg[maxn];
vector<int> G2[maxn];

inline void Dijkstra(int s) {
    memset(d1, 0x3f, sizeof d1);
    d1[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push(make_pair(0, s));
    while(!pq.empty()) {
        pii cur = pq.top(); pq.pop();
        int di = cur.first, no = cur.second;
        if(d1[no] != di) continue;
        for(int i = head[no]; i ; i = nxt[i]) {
            int to = e[i].to;
            if(di + e[i].w < d1[to]) {
                d1[to] = di + e[i].w;
                pq.push(make_pair(d1[to], to));
            }
        }
    }
}

int topo[maxn], topo_clock = 0;
inline bool toposort() {
    topo_clock = 0;
    queue<int> q;
    for(int i = 1; i <= n; ++i) {
        if(zdeg[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        topo[cur] = ++topo_clock;
        for(auto v : G2[cur]) {
            if(--zdeg[v] == 0) q.push(v);
        }
    }
    if(topo_clock < n) return true;
    return false;
}
bool cmp(int xp, int yp) {
    if(d1[xp] < d1[yp]) return true;
    if(d1[xp] == d1[yp] && topo[xp] < topo[yp]) return true;
    return false;
}

int seq[maxn];
inline void Sort() {
    for(int i = 1; i <= n; ++i) seq[i] = i;
    sort(seq + 1, seq + 1 + n, cmp);
}

inline int mo(int v) { 
    if(v >= mod) v -= mod;
    if(v < 0) v += mod;
    return v;
}
inline void addn(int& x, int y) {x = mo(x + y);}

int dp[maxn][56];
inline void DP() {
    memset(dp, 0, sizeof dp);
    dp[seq[1]][0] = 1;
    for(int c = 0; c <= k; ++c) {
        for(int t = 1; t <= n; ++t) {
            int cur = seq[t], ans = dp[cur][c];
            if(ans == 0) continue;
        
            for(int i = head[cur]; i ; i = nxt[i]) {
                int to = e[i].to;
                int subs = d1[cur] + e[i].w + c - d1[to];
                if(subs < 0 || subs > k) continue;
                addn(dp[to][subs], ans);
            }
        }
    }
}

int main(){
    int T; scanf("%d", &T);
    for(kase = 1; kase <= T; ++kase) {
        memset(zdeg, 0, sizeof zdeg);
        memset(head, 0, sizeof head);
        ecnt = 0;
        scanf("%d%d%d%d", &n, &m, &k, &mod);
        rep(i, n) G2[i].clear();
        for(int i = 1; i <= m; ++i) {
            int f, t, c;
            scanf("%d%d%d", &f, &t, &c);
            addedge(f, t, c);
            if(c == 0) G2[f].push_back(t), zdeg[t]++;
        }
        if(toposort()) {puts("-1"); continue;};
        Dijkstra(1);
        Sort();
        DP();
        int ans = 0;
        for(int c = 0; c <= k; ++c) {
            addn(ans, dp[n][c]);
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
