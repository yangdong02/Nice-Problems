#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define INFL 0x3f3f3f3f3f3f3fLL
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

#define ABS(x) ( (x)>0 ? (x) : (-(x)) )

const int maxn = 2002000;
int tot = 0;
ll n, q, a[maxn], c[maxn], bk[maxn], vis[maxn], gp = INFL;
multiset<ll> Inc, dif;
multiset< ll, greater<ll> > Dec;

int main() {
    read(n, q);
    rep(i, n) {
        read(a[i]), bk[i] = a[i];
        Inc.insert(a[i]);
        Dec.insert(a[i]);
    }
    for(int i = 1; i < n; ++i) {
        dif.insert(ABS(a[i] - a[i+1]));
    }
    for(multiset<ll>::iterator it = Inc.begin(); it != Inc.end(); ++it)
        c[++tot] = *it;
    rep(i, n - 1) gp = min(gp, ABS(c[i] - c[i+1]));
    Inc.insert(INFL), Inc.insert(-INFL);
    Dec.insert(INFL), Dec.insert(-INFL);
    while(q--) {
        char opt[30];
        scanf("%s", opt);
        if(opt[0] == 'M') {
            ll ans;
            if(opt[4] == 'S') ans = gp;
            if(opt[4] == 'G') ans = *dif.begin();
            printf("%lld\n", ans);
        } else {
            ll pos, x; read(pos, x);
            ll Next = *Inc.lower_bound(x), Prev = *Dec.lower_bound(x);
            Inc.insert(x), Dec.insert(x);
            gp = min(gp, min(Next - x, x - Prev));
            
            ll ini = ABS(a[pos + 1] - bk[pos]);
            ll d1 = -1, d2 = ABS(a[pos + 1] - x);
            if(!vis[pos]) vis[pos] = true, d1 = ABS(a[pos] - x);
            else d1 = ABS(bk[pos] - x);

            dif.erase(dif.find(ini));
            dif.insert(d1);
            dif.insert(d2);
            bk[pos] = x;
            
        }
    }
    return 0;
}
