/*
Link: Contest Hunter round 46 problem A 磁力块'
Source: 算法竞赛进阶指南 0x44 分块
Solution:
  1. BFS frame
  2. How to add stones into the queue efficiently?
     This is equivalent to find numbers which satisfy
     Distance <= Current_Radius and Mass <= Current_Force
     This is a partial set problem and can be solved with
     balanced tree.
  3. However, we can simply sort the array in mass first, 
     then split the sequence into T blocks. In each
     block sort the stones according to distance. Then we
     can find for each stone the array is like this:
     [Light stones] [Light stones with heavy ones] [Heavy stones]
     We ignore the heavy ones, as we can choose nothing from them.
     There can be only one block which contains light stone together
     with heavy ones, as the sorting guarantees. So we can simply brute
     force in O(n/T) for this part. For light stones, we record a pointer which
     stands for the left bound of the block. As each element will only be
     considered once, this will only take O(T) time.
Overall complexity: O(n sqrt(n)) (we choose T = sqrt(n))
*/

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
template<typename T, typename... Args> void read(T &x, Args&... args) {
    read(x);
    read(args...);
}
const int maxn = 250400, maxB = 600;
int x0, y0, n;
bool vis[maxn];
inline ll sqr(int x) { return 1LL * x * x; }
struct Stone {
    ll d, r;
    int m, f;
    inline void init() {
        int x, y;
        read(x, y, m, f, r);
        d = sqr(x0 - x) + sqr(y0 - y);
        r = r * r;
    }
} s[maxn];

inline bool cmp1( Stone s1, Stone s2) { return s1.m < s2.m; }
inline bool cmp2( Stone s1, Stone s2) { return s1.d < s2.d; }

int t, len, L[maxB], R[maxB], p[maxB], cnt = 0;

inline void Refactor(int x) {
    int po = R[x];
    for(int i = R[x]; i >= L[x]; --i) {
        if(vis[i]) continue;
        swap(vis[po], vis[i]);
        swap(s[po], s[i]);
        po--;
    }
    p[x] = po + 1;
}

int main() {
    read(x0, y0, s[0].f, s[0].r, n);
    s[0].r = s[0].r * s[0].r;
    rep(i, n) s[i].init();
    sort(s + 1, s + n + 1, cmp1);

    t = sqrt(n + 0.5), len = n / t;
    for(int i = 1; i <= t; ++i) {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
    }
    if(R[t] < n) t++, L[t] = R[t-1] + 1, R[t] = n;
    for(int i = 1; i <= t; ++i) {
        sort(s + L[i], s + R[i] + 1, cmp2);
        p[i] = L[i];
    }
    queue<Stone> q; q.push(s[0]);
    while(!q.empty()) {
        Stone tp = q.front(); q.pop();
        Stone* cur = &tp;
        for(int i = 1; i <= t; ++i) {
            while(s[p[i]].m <= tp.f && s[p[i]].d <= tp.r && p[i] <= R[i])
                q.push(s[p[i]]), cnt++, vis[p[i]++] = true;
            if(p[i] > R[i]) continue;
            if(s[p[i]].m > cur->f) {
                for(int j = p[i] + 1; j <= R[i]; ++j)
                    if(s[j].m <= cur->f && s[j].d <= cur->r)
                        q.push(s[j]), cnt++, vis[j] = true;
                Refactor(i);
                break;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
