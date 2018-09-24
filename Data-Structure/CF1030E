// A data structure problem which requires no advanced DS
// It's easy to see that we only need to count the intevals [l...r] such that sum(l, r) >= 2 * max(l, r) and sum(l, r) % 2 == 0
// The bruteforce solution has complexity O(n ^ 2) which is not able to pass
// One key observation is that every a[i] < 64 so 2 * max(l, r) < 128 ; a[i] > 0 so only when r - l < 128 can sum(l, r) < 2* max exist
// For each l, We can calculate naively when sum(l, r) < 128 and add them to answer
// when sum(l, r) >= 128, we should calculate how many r s.t. sum(l, r) is a multiple of 2
// This is quite easy using a prefix sum.
// Overall complexity: O(nlogn) RMQ initialize and O(128 * n) for calculating the answer.

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
inline int popcount(ll x){
    int cnt = 0;
    for(; x; x >>= 1) if(x & 1) cnt++;
    return cnt;
}
const int maxn = 300200;
template <typename T> inline void read(T& x){ int w = 1; T data = 0; char ch = getchar(); while(!isdigit(ch) && ch != '-') ch = getchar(); if(ch == '-') w = -1, ch = getchar(); while(isdigit(ch)) data = 10 * data + ch - '0', ch = getchar(); x = data * w; }
template <typename T> void write(T x){ if (x < 0) putchar('-'),x = ~x + 1; if (x > 9) write(x / 10); putchar( x % 10 + '0'); }
template <typename T> inline void writeln(T x){ write(x), putchar('\n'); }
int a[maxn], n, pre[maxn], d[maxn][30], even[maxn], pre2[maxn];
inline void RMQ_init(){
    rep(i, n) d[i][0] = a[i];
    for(int j = 1; (1<<j) <= n; ++j)
        for(int i = 1; i + (1<<j) <= n + 1; ++i)
            d[i][j] = max(d[i][j-1], d[i+(1<<(j-1))][j-1]);
}
int RMQ(int l, int r){
    int k = 0;
    while((1 << (k+1)) <= r - l + 1) k++;
    return max(d[l][k], d[r-(1<<k)+1][k]);
}
int main(){
    read(n);
    rep(i, n){
        ll x; read(x);
        a[i] = popcount(x);
        pre[i] = pre[i-1] + a[i];
        even[i] = !(pre[i] & 1);
        pre2[i] = pre2[i - 1] + even[i];
    }
    RMQ_init();
    ll cnt = 0;
    for(register int i = 1; i <= n; ++i){
        ll sum = a[i];
        for(register int j = i + 1; j <= n; ++j){
            sum += a[j];
            if( !(sum & 1) && (sum >= (RMQ(i, j) << 1)) ) cnt++;
            if(sum >= 128) {
                ll ecnt = pre2[n] - pre2[j], ocnt = n - j - ecnt;
                bool odd = pre[i - 1] & 1;
                cnt += odd ? ocnt : ecnt;
                break;
            }
        }
    }
    printf("%lld\n", cnt);
    return 0;
}
