// Link: https://www.luogu.org/problemnew/show/P1092
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 28;
int n, a[maxn], b[maxn], s[maxn], val[maxn], vis[maxn];
char ba[maxn], bb[maxn], bc[maxn];
bool Prune() { // This prune is really important, which reduces execution time from TLE to 15ms
    for(int i = 0; i < n; ++i) {
        int A = val[a[i]], B = val[b[i]], C = val[s[i]];
        if(A == -1 || B == -1 || C == -1) continue;
        if( ((A+B)%n != C) && ((A+B+1)%n != C) ) return true;
    }
    return false;
}
void dfs(int d, bool add) {
    if(d == n) {
        for(int i = 0; i < n; ++i)
            printf("%d%c", val[i], " \n"[i==n-1]);
        exit(0);
    }
    if(Prune()) return;
    int ix = val[a[d]], iy = val[b[d]], iz = val[s[d]];
    bool f1 = (ix == -1), f2 = (iy == -1), f3 = (iz == -1);
    for(int x = (f1 ? (n-1) : ix); x >= (f1 ? 0 : ix); --x) if(!f1 || !vis[x]){
        for(int y = (f2 ? (n-1) : iy); y >= (f2 ? 0 : iy); --y) if((!f2 || !vis[y]) && ((a[d] != b[d] && y != x) || (a[d] == b[d] && y == x))){
            int ze = x + y + add - ((x+y+add>=n) ? n : 0), ad = (x + y + add >= n);
            if(!f3 && ze != iz) continue;
            if(f3 && vis[ze]) continue;
            if((s[d] != a[d] && ze == x) || (s[d] != b[d] && ze == y)) continue;
            if((s[d] == a[d] && ze != x) || (s[d] == b[d] && ze != y)) continue;
            val[a[d]] = x, val[b[d]] = y, val[s[d]] = ze;
            vis[x] = vis[y] = vis[ze] = true;
            dfs(d + 1, ad);
            val[a[d]] = ix, val[b[d]] = iy, val[s[d]] = iz;
            vis[x] = (ix != -1);
            vis[y] = (iy != -1);
            vis[ze] = (iz != -1);
        }
    }
}
int main(){
    memset(val, -1, sizeof val);
    scanf("%d%s%s%s", &n, ba, bb, bc);
    for(int i = 0; i < n; ++i) {
        a[n-i-1] = ba[i] - 'A';
        b[n-i-1] = bb[i] - 'A';
        s[n-i-1] = bc[i] - 'A';
    }
    dfs(0, 0);
    
    return 0;
}
