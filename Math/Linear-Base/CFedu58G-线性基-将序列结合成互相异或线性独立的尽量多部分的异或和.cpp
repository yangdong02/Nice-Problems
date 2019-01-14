#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 200200;
ll base[100], n, a[maxn], sum = 0, ans = 0;
bool ins(ll x) {
    for(int i = 60; i >= 0; --i) {
        if((x >> i) & 1) {
            if(base[i] == 0) { base[i] = x; return true; }
            else x ^= base[i];
        }
    }
    return false;
}

ll tot = 0;
int main() {
    scanf("%lld", &n);
    rep(i, n) scanf("%lld", &a[i]), tot ^= a[i];
    if(tot == 0) {puts("-1"); return 0;}
    rep(i, n) {
        sum ^= a[i];
        if(ins(sum)) sum = 0, ans++;
    }
    printf("%lld\n", ans);
    
    return 0;
}
