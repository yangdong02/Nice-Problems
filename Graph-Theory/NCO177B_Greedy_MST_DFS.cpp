// https://www.nowcoder.com/acm/contest/177/B
// Add some edges to make all the vertices have even degree
// Edge costs are pow(2, i)

// Solution:
// Calculate the degree of each vertex
// Find the minimal spanning tree, and do a dfs from leaves (DSU, MST, DFS)
// Add edges v -> fa[v] on the spanning tree when v has odd degree (Greedy)
// We can show that this method is optimal

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}

const int maxn = 1000300, mod = 998244353;
namespace dsu {
    int fa[maxn];
    inline void init(int sz) { rep(i, sz) fa[i] = i;}
    int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
    inline bool merge(int x, int y) {
        x = find(x), y = find(y);
        if(x != y ) {fa[x] = y; return true;}
        return false;
    }
}

int n, m, head[maxn], nxt[maxn << 1], ecnt = 0;
int even[maxn];
struct edge{
    int from, to , w;
    edge(int x = 0, int y = 0, int z = 0) : from(x), to(y), w(z) { }
} e[maxn];
inline void addedge(int x, int y, int z) {
    e[++ecnt] = edge(x, y, z);
    nxt[ecnt] = head[x];
    head[x] = ecnt;
}

ll ans = 0;
inline ll add(ll x, ll y) {return x + y - ((x + y) >= mod ? mod : 0);}
inline ll mul(ll x, ll y) {return x * y % mod;}
inline ll qpow(ll x, ll y) {
    ll ret = 1;
    for(; y; y >>= 1, x = mul(x, x))
        if(y & 1) ret = mul(ret, x);
    return ret;
}

void dfs(int v, int fa) {
    int faedge;
    for(int i = head[v]; i ; i = nxt[i]) 
        if(e[i].to != fa) dfs(e[i].to, v);
        else faedge = i;
    if(even[v]) {
        even[v] ^= 1, even[fa] ^= 1;
        ans = add(ans, qpow(2, e[faedge].w));
    }   
} 

int main(){
    scanf("%d%d", &n, &m);
    ans = (qpow(2, m + 1) + mod - 2) % mod ;
    dsu::init(n);
    rep(i, m) {
        int x, y; read(x), read(y);
        if(dsu::merge(x, y)) addedge(x, y, i), addedge(y, x, i);
        even[x] ^= 1, even[y] ^= 1;
    }

    dfs(1, -1);
    printf("%lld\n", ans);
    return 0;
}
