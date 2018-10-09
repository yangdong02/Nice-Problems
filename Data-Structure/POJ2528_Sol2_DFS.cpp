// An amazing approach which only used 15ms and ~1000 Byte code length

#include<cstdio>
#include<cstring>
#include<cctype>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}

const int N = 10020;
int ans = 0, st[N], ed[N], n;
bool vis[N];

void dfs(int l, int r, int x) {
    if(!x) return;
    if(l <= ed[x] && r >= st[x]) { // [l, r] Intersects interval x
        if(!vis[x]) vis[x] = true, ans++;
        if(l < st[x]) dfs(l, st[x] - 1, x - 1);
        if(r > ed[x]) dfs(ed[x] + 1, r, x - 1);
    } else dfs(l, r, x - 1);
}

int main(){
    int T; read(T);
    while(T--) {
        ans = 0;
        read(n); memset(vis, 0, sizeof vis);
        rep(i, n) read(st[i]), read(ed[i]);
        dfs(1, 10000000, n);
        printf("%d\n", ans);
    }
    
    return 0;
}
