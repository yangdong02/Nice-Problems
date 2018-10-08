// Link: https://cn.vjudge.net/problem/HDU-3038
// A really nice problem, which requires thinking to come up with dsu solution

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
#define int long long
const int maxn = 200200;
int n, q, fa[maxn], sum[maxn];
inline void init(int sz) {
    for(int i = 0; i <= sz; ++i) fa[i] = i;
    memset(sum, 0, sizeof sum);
}
int find(int x) {
    if(x == fa[x]) return x;
    int ans = find(fa[x]);
    sum[x] += sum[fa[x]];
    return fa[x] = ans;
}
inline void merge(int x, int y, int v) {
    int from = find(x), des = find(y);
    v = v - sum[x] + sum[y];
    sum[from] = v;
    fa[from] = des;
}
signed main(){
    while(~scanf("%lld%lld", &n, &q)) {
        int cnt = 0; init(n);
        while(q--) {
            int l, r, v;
            scanf("%lld%lld%lld", &l, &r, &v); l--;
            if(find(l) == find(r)) {
                if(sum[l] != sum[r] + v) cnt++;
            } else merge(l, r, v);
        }
        printf("%lld\n", cnt);
    }
    
    return 0;
}
