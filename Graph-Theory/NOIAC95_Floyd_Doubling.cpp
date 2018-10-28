/*
Link: http://noi.ac/contest/27/problem/95
Source: NOI.AC NOIP virtual contest round 3 Problem A.

Description: (Similar to BZOJ 4773)
  Find the positive cycle with minimum length in one graph
  or report there is none.
  
Solution:
  Change the problem into finding a negative cycle.
  When a negative cycle is detected, floyd algorithm will find
  for some vertex x d[x][x] < 0. Let's focus on this property.
  Use doubling floyd on path length 9 times until such negative value 
  exists. (if there's none, puts 0) .Then use the similar technique 
  in finding LCA to find the maximum length L such that no d[x][x] < 0
  exists. Then the answer should be L + 1
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
template<typename T> void read(T &x) {
    x = 0; int sgn = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') sgn = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= sgn;
}

const int maxn = 310, maxm = 100000;
int n, m;
struct Mat {
    ll d[maxn][maxn];
    Mat() {
        memset(d, 0x3f, sizeof d);
        for(int i = 1; i <= 300; ++i) d[i][i] = 0;
    }
    inline Mat operator * (const Mat& mt) const {
        Mat res;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                for(int k = 1; k <= n; ++k)
                    res.d[i][j] = min(res.d[i][j], d[i][k] + mt.d[k][j]);
        return res;
    }
    inline bool Neg () {
        rep(i, n) if(d[i][i] < 0) return true;
        return false;
    }
} f[10], M;
int main(){
    read(n), read(m);
    rep(i, m) {
        int x, y, c1, c2;
        read(x), read(y), read(c1), read(c2);
        f[0].d[x][y] = -c1;
        f[0].d[y][x] = -c2;
    }
    int flag = -1, ans = 0;
    for(int i = 1; i <= 9; ++i) {
        f[i] = f[i - 1] * f[i - 1];
        if(f[i].Neg())  {flag = i; break;}
    }
    if(flag == -1) {
        puts("0");
        return 0;
    }
    for(int i = flag - 1; i >= 0; --i) {
        Mat tmp = M * f[i];
        if(!tmp.Neg()) M = tmp, ans += (1 << i);
    }
    printf("%d\n", ans + 1);
    return 0;
}
