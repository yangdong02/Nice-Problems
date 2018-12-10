#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 5000;
int sum = 0, n;
ll base[80];
struct item {
    int w;
    ll d;
    bool operator < (const item& it) const {
        return w > it.w;
    }
} t[maxn];
inline bool ins(ll x) {
    for(int i = 62; i >= 0; --i) {
        if(x >> i & 1) {
            if(base[i]) x ^= base[i];
            else { base[i] = x ; return true; }
        }
    }
    return false;
}
int main() {
    scanf("%d", &n);
    rep(i, n) scanf("%lld%d", &t[i].d, &t[i].w);
    sort(t + 1, t + 1 + n);
    for(int i = 1; i <= n; ++i)
        if(ins(t[i].d)) sum += t[i].w;
    printf("%d\n", sum);
    
    return 0;
}
