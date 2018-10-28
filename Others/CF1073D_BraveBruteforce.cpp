/*
Link: http://codeforces.com/contest/1073/problem/D
Source: Educational Codeforces Round 53 (Rated for Div. 2)

Solution:
  This problem seems to require segment tree, Fenwick
  tree, etc. However, indeed the bruteforce solution
  has right time complexity and will be accepted. In fact, 
  when we go through the round once, T will become T % sum, 
  (sum is the greatest possible money we will spend and sum <= T)
  which is less than T / 2. So the bruteforce solution has complexity
  O(nlogn) which is the same as segment tree.
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define int long long
using namespace std;
typedef long long ll;
const int maxn = 200200;
int n, T, a[maxn], ans = 0LL;
signed main(){
    scanf("%lld%lld", &n, &T);
    rep(i, n) scanf("%lld", &a[i]);
    while(1) {
        int tot = 0, cnt = 0;
        for(int i = 1; i <= n; ++i)
            if(tot + a[i] <= T) cnt++, tot += a[i];
        if(cnt == 0) break;
        ans += (T / tot) * cnt, T %= tot;
    }
    printf("%lld\n", ans);
    return 0;
}
