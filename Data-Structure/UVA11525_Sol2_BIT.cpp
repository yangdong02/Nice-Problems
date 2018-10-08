// The problem is equivalent to support these operations: 
//  1. find kth smallest
//  2. delete elements
//  The first approach is using balanced binary search tree, as shown below
//  The second solution is to use binary indexed tree, which I think is quite elegant
// Link: https://cn.vjudge.net/problem/UVA-11525
// Introduction to this solution : https://www.cnblogs.com/wuyiqi/archive/2011/12/25/2301071.html

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 100100;
int n;

struct Fenwick {
    #define lowbit(x) (x & (-x))
    int c[maxn + 100];
    inline void add(int x, int v) {
        for(; x <= maxn; x += lowbit(x))
            c[x] += v;
    }
    inline int find_kth(int k) { // kth smallest
        int ans = 0, cnt = 0, i;
        for(i = 20; i >= 0; --i) {
            ans += 1 << i;
            if(ans >= maxn || c[ans] + cnt >= k) ans -= 1 << i;
            else cnt += c[ans];
        }
        return ans + 1;
    }
} t;
int main(){
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        rep(i, n) t.add(i, 1);
        int fin = 0;
        rep(i, n) {
            int k, ans; scanf("%d", &k);
            ans = t.find_kth(k + 1);
            printf("%d%c", ans, ++fin == n ? '\n' : ' ');
            t.add(ans, -1);
        }
    }
    
    return 0;
}
