/* Problem: (Div1 E) Random Forest Rank
Link: http://codeforces.com/contest/1067/problem/E
Source: Codeforces Round #518 (Div. 1) [Thanks, Mail.Ru!]
Overview: Math conclusion + dp on tree

Solution:
  Conclusion: Rank of a forest is twice the size of maximal matching.
  Proof: See editorial https://codeforces.com/blog/entry/62688 (really elegant)
  DP solution:
    We will calculate the probability each vertex will make to matching and contribute to the answer
    (assume one vertex makes contribution iff it forms matching with one of its sons)
    Then, a vertex makes no contribution only if its all linked sons are choson. That is:
    no[v] = MUL [(1 + yes[son]) / 2]
    yes[v] = 1 - no[v]
*/


#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 500200, mod = 998244353, inv2 = (mod + 1) / 2;
inline int add (int x, int y) {return x + y - ((x + y >= mod) ? mod: 0);}
inline int mul (int x, int y) {return 1LL * x * y % mod;}
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = mul(x, x))
        if(y & 1) ret = mul(ret, x);
    return ret;
}

vector<int> G[maxn];
int n, f[maxn], g[maxn], ans = 0; // f: chosen, g: not chosen
void dfs(int v, int fa) {
    int &no = g[v], &yes = f[v]; no = 1;
    for(auto u : G[v]) if(u != fa) {
        dfs(u, v);
        no = mul(no, mul(inv2, add(1, f[u])));
    }
    yes = add(1 + mod, -no);
    ans = add(ans, yes);
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, -1);
    ans = mul(ans, qpow(2, n));
    printf("%d\n", ans);
    return 0;
}
