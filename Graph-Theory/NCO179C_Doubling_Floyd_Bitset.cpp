/*
Link: https://www.nowcoder.com/acm/contest/179/C
Source: Nowcoder NOIP virtual contest round 7

Description:
  Determine whether or not we can go from vertex u to v in a 
  path which length is exactly len in O(q * n^3 * logn / 64)
  ( n <= 100, m <= 10000, q <= 1000 )

Solution:
1.Use floyd doubling algorithm (a little bit similar to matrix
  multiplication.): Precalculate g[i][from][to] matrix which means 
  whether we can go from "from" to "to" in exactly 2^i length
  We can define '*' sign in Matrix. Then to get whether we can go in
  arbitrary number len, just split it into some binary 1s and multiply
  them togeter. 
    e.g. for len = 5(101) we will use g[0] * g[2]
2.This is not enough to fit in the time limit in this problem. We can find that
  the elements of the array is either 0 or 1, so we will use bitsets to store them
  and use bitset OR to make complexity reduced to its 1 / 64
Similar question: http://noi.ac/contest/27/problem/95 
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 202;
int n, m, q;
struct Mat {
    bitset<maxn> b[maxn];
    inline Mat&& operator * (const Mat& mt) const {
        Mat r;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) if(b[i][j]) {
                r.b[i] |= mt.b[j];
            }
        }
        return move(r); 
        // NO need to use move() ? Seems it runs slower than without move on nowcoder
    }
} g[40];
inline bool judge(int x, int y, ll len) {
    Mat t; bool Set = false;
    for(int i = 36; i >= 0; --i)
        if(len & (1LL << i)) {
            if(Set) t = t * g[i];
            else t = g[i], Set = true;
        }
    return t.b[x][y];
}
int main(){
    scanf("%d%d", &n, &m);
    rep(i, m) {
        int x, y; scanf("%d%d", &x, &y);
        g[0].b[x][y] = true;
    }
    scanf("%d", &q);
    for(int k = 1; k <= 38; ++k) {
        g[k] = g[k - 1] * g[k - 1];
    }
    while(q--) {
        int x, y; ll len;
        scanf("%lld%d%d", &len, &x, &y);
        puts(judge(x, y, len) ? "YES" : "NO");
    }
    return 0;
}
