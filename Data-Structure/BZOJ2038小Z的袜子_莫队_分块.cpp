 
#include<bits/stdc++.h>
#define rep(i, n) for(register int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
  
const int maxn = 50500, maxB = 500;
int a[maxn], n, m, L[maxB], R[maxB], pos[maxn], t = 0, lenb;
int cnt[maxn], lenq[maxn];
ll ans[maxn], cur_ans = 0, num[maxn], dem[maxn];
  
struct Query { int l, r, id; } q[maxn];
inline bool cmp1(const Query &q1, const Query &q2) {return q1.l < q2.l; }
inline bool cmp2(const Query &q1, const Query &q2) {
    return pos[q1.l] < pos[q2.l] || (pos[q1.l] == pos[q2.l] && q1.r < q2.r); 
}
ll gcd(ll x, ll y) { return y == 0LL ? x : gcd(y, x % y); }
  
#define Ins(v) { cur_ans += (2 * cnt[v] + 1), cnt[v]++; }
#define Del(v) { cur_ans -= (2 * cnt[v] - 1), cnt[v]--; }
 
int main() {
    scanf("%d%d", &n, &m);
    rep(i, n) scanf("%d", &a[i]);
    rep(i, m) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
        lenq[i] = q[i].r - q[i].l + 1;
    }
    sort(q + 1, q + m + 1, cmp1);
    t = sqrt(m + 0.5), lenb = m / t;
    for(int i = 1; i <= m; ++i)
        pos[i] = (i - 1) / lenb + 1;
    sort(q + 1, q + m + 1, cmp2);
    for(int i = q[1].l; i <= q[1].r; ++i) cnt[a[i]]++;
    for(int i = 1; i <= 50000; ++i) cur_ans += 1LL * cnt[i] * cnt[i];
    ans[q[1].id] = cur_ans;
    int cur_l = q[1].l, cur_r = q[1].r;
    for(int qn = 2; qn <= m; ++qn) {
        int nl = q[qn].l, nr = q[qn].r;
        if(cur_r < nr) for(int i = cur_r + 1; i <= nr; ++i) Ins(a[i]);
        if(cur_r > nr) for(int i = cur_r; i > nr; --i) Del(a[i]);
          
        if(cur_l > nl) for(int i = cur_l - 1; i >= nl; --i) Ins(a[i]);
        if(cur_l < nl) for(int i = cur_l; i < nl; ++i) Del(a[i]);
        ans[q[qn].id] = cur_ans;
        cur_l = nl, cur_r = nr;
    }
    for(int i = 1; i <= m; ++i) {
        ll len = lenq[i], gc;
        num[i] = ans[i] - len;
        dem[i] = len * (len - 1);
        gc = gcd(num[i], dem[i]);
        num[i] /= gc, dem[i] /= gc;
        if(num[i] == 0) dem[i] = 1;
        printf("%lld/%lld\n", num[i], dem[i]);
    }
    return 0;
}
